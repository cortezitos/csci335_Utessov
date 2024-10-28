module bitty_core (
    input wire clk,
    input wire reset,
    input wire run,
    input wire [15:0] instruction,
    output wire done,
    output reg [15:0] reg_c_out,
    output reg [15:0] reg_0_out,
    output reg [15:0] reg_1_out,
    output reg [15:0] reg_s_out

);
    wire [15:0] alu_out, mux_out;
    wire carry_out, compare;
    wire [3:0] sel;
    wire [2:0] mux_sel;
    wire mode, en_s, en_c, en_0, en_1, en_2, en_3, en_4, en_5, en_6, en_7;

    wire [15:0] reg_2_out, reg_3_out, reg_4_out, reg_5_out, reg_6_out, reg_7_out;

    assign reg_0_out = 20;
    assign reg_1_out = 30;

    control_unit ctrl_unit (
        .instruction(instruction),
        .run(run),
        .clk(clk),
        .reset(reset),
        .sel(sel),
        .mux_sel(mux_sel),
        .mode(mode),
        .en_s(en_s),
        .en_c(en_c),
        .en_0(en_0),
        .en_1(en_1),
        .en_2(en_2),
        .en_3(en_3),
        .en_4(en_4),
        .en_5(en_5),
        .en_6(en_6),
        .en_7(en_7),
        .done(done)
    );


    register reg_0 (.d_in(reg_c_out), .reset(reset), .clk(clk), .en(en_0), .d_out(reg_0_out));
    register reg_1 (.d_in(reg_c_out), .reset(reset), .clk(clk), .en(en_1), .d_out(reg_1_out));
    register reg_2 (.d_in(reg_c_out), .reset(reset), .clk(clk), .en(en_2), .d_out(reg_2_out));
    register reg_3 (.d_in(reg_c_out), .reset(reset), .clk(clk), .en(en_3), .d_out(reg_3_out));
    register reg_4 (.d_in(reg_c_out), .reset(reset), .clk(clk), .en(en_4), .d_out(reg_4_out));
    register reg_5 (.d_in(reg_c_out), .reset(reset), .clk(clk), .en(en_5), .d_out(reg_5_out));
    register reg_6 (.d_in(reg_c_out), .reset(reset), .clk(clk), .en(en_6), .d_out(reg_6_out));
    register reg_7 (.d_in(reg_c_out), .reset(reset), .clk(clk), .en(en_7), .d_out(reg_7_out));

    register reg_s (.d_in(mux_out), .reset(reset), .clk(clk), .en(en_s), .d_out(reg_s_out));
    register reg_c (.d_in(alu_out), .reset(reset), .clk(clk), .en(en_c), .d_out(reg_c_out));


    multiplexer mux (
        .reg_0(reg_0_out), .reg_1(reg_1_out), .reg_2(reg_2_out), .reg_3(reg_3_out),
        .reg_4(reg_4_out), .reg_5(reg_5_out), .reg_6(reg_6_out), .reg_7(reg_7_out),
        .mux_sel(mux_sel),
        .d_out(mux_out)
    );

    alu alu (
        .in_a(reg_s_out),
        .in_b(mux_out),
        .select(sel),
        .mode(mode),
        .carry_out(carry_out),
        .compare(compare),
        .alu_out(alu_out)
    );
endmodule


module control_unit (
    input  wire [15:0] instruction,
    input  wire        run,
    input  wire        clk,
    input  wire        reset,
    output reg  [3:0]  sel,
    output reg  [2:0]  mux_sel,
    output reg         mode,
    output reg         en_s,
    output reg         en_c,
    output reg         en_0,
    output reg         en_1,
    output reg         en_2,
    output reg         en_3,
    output reg         en_4,
    output reg         en_5,
    output reg         en_6,
    output reg         en_7,
    output reg        done
);

    reg [1:0] i = 0;

    always @(posedge clk) begin
        if (reset) begin
            i <= 0;
            en_s <= 0;
            en_c <= 0;
            en_0 <= 0;
            en_1 <= 0;
            en_2 <= 0;
            en_3 <= 0;
            en_4 <= 0;
            en_5 <= 0;
            en_6 <= 0;
            en_7 <= 0;
            done <= 0;
        end else if (run) begin
            done <= 0;
            case(i)
                2'd0: begin
                    mux_sel <= instruction[15:13];
                    en_s <= 1;
                    i <= 1;
                end
                2'd1: begin
                    en_s <= 0;
                    mux_sel <= instruction[12:10];
                    en_c <= 1;
                    sel <= instruction[6:3];
                    mode <= instruction[2];
                    i <= 2;
                end
                2'd2: begin
                    en_c <= 0;
                    case(instruction[15:13])
                        3'd0: en_0 <= 1;
                        3'd1: en_1 <= 1;
                        3'd2: en_2 <= 1;
                        3'd3: en_3 <= 1;
                        3'd4: en_4 <= 1;
                        3'd5: en_5 <= 1;
                        3'd6: en_6 <= 1;
                        3'd7: en_7 <= 1;
                    endcase
                    i <= 0;
                    done <= 1;
                end
                default: i <= 0;

            endcase
        end
    end

endmodule


module alu (
    input  wire [15:0] in_a,
    input  wire [15:0] in_b,
    input  wire [3:0]  select,
    input  wire        mode,
    output reg        carry_out,
    output reg        compare,
    output reg [15:0] alu_out
);


    always @(*) begin
        case(mode)
            1'b0: 
            begin
                carry_out = 0;  
                case (select)
                    4'b0000: alu_out = in_a;
                    4'b0001: alu_out = in_a | in_b;
                    4'b0010: alu_out = in_a | ~in_b;
                    4'b0011: alu_out = -1;
                    4'b0100: alu_out = in_a | (in_a & ~in_b);
                    4'b0101: {carry_out, alu_out} = {1'b0, (in_a | in_b)} + {1'b0, (in_a & ~in_b)};
                    4'b0110: alu_out = in_a - in_b - 1;
                    4'b0111: alu_out = (in_a & ~in_b) - 1;
                    4'b1000: {carry_out, alu_out} = {1'b0, in_a} + {1'b0, (in_a & in_b)};
                    4'b1001: {carry_out, alu_out} = {1'b0, in_a} + {1'b0, in_b};
                    4'b1010: {carry_out, alu_out} = {1'b0, (in_a | ~in_b)} + {1'b0, (in_a & in_b)};
                    4'b1011: alu_out = (in_a & in_b) - 1;
                    4'b1100: {carry_out, alu_out} = {1'b0, in_a} + {1'b0, in_a};
                    4'b1101: {carry_out, alu_out} = {1'b0, (in_a | in_b)} + {1'b0, in_a};
                    4'b1110: {carry_out, alu_out} = {1'b0, (in_a | ~in_b)} + {1'b0, in_a};
                    4'b1111: alu_out = in_a - 1;
                    default: alu_out = 16'b0;
                endcase
            end

            1'b1: 
            begin
                case(select)
                    4'b0000: alu_out = ~in_a;
                    4'b0001: alu_out = ~(in_a | in_b);
                    4'b0010: alu_out = ~in_a & in_b;
                    4'b0011: alu_out = 16'h0000;
                    4'b0100: alu_out = ~(in_a & in_b);
                    4'b0101: alu_out = ~in_b;
                    4'b0110: alu_out = in_a ^ in_b;
                    4'b0111: alu_out = in_a & ~in_b;
                    4'b1000: alu_out = ~in_a | in_b;
                    4'b1001: alu_out = ~(in_a ^ in_b);
                    4'b1010: alu_out = in_b;
                    4'b1011: alu_out = in_a & in_b;
                    4'b1100: alu_out = 16'hFFFF; 
                    4'b1101: alu_out = in_a | ~in_b;
                    4'b1110: alu_out = in_a | in_b;
                    4'b1111: alu_out = in_a;
                    default: alu_out = 16'h0000; 
                endcase
            end
        endcase
        compare = (in_a == in_b) ? 1 : 0;
    end

endmodule

module multiplexer (
    input  wire [15:0] reg_0,
    input  wire [15:0] reg_1,
    input  wire [15:0] reg_2,
    input  wire [15:0] reg_3,
    input  wire [15:0] reg_4,
    input  wire [15:0] reg_5,
    input  wire [15:0] reg_6,
    input  wire [15:0] reg_7,
    input  wire  [2:0] mux_sel,
    output reg  [15:0] d_out
);

    always @(*) begin
        case (mux_sel)
            3'd0: d_out = reg_0;
            3'd1: d_out = reg_1;
            3'd2: d_out = reg_2;
            3'd3: d_out = reg_3;
            3'd4: d_out = reg_4;
            3'd5: d_out = reg_5;
            3'd6: d_out = reg_6;
            3'd7: d_out = reg_7;
            default: d_out = 16'd0;
        endcase
    end
endmodule


module register (
    input  wire [15:0] d_in,
    input  wire        reset,
    input  wire        clk,
    input  wire        en,
    output reg  [15:0] d_out
);

    always @(*) begin
        if (reset) begin
            d_out = 16'd0;
        end
        else if (en) begin
            d_out = d_in;
        end
    end

endmodule



