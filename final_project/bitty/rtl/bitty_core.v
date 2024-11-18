module bitty_core (
    input wire clk,
    input wire reset,
    input wire run,
    output wire [15:0] instruction,
    output wire done,
    output reg [15:0] reg_0_out,
    output reg [15:0] reg_1_out,
    output reg [15:0] reg_2_out,
    output reg [15:0] reg_3_out,
    output reg [15:0] reg_4_out,
    output reg [15:0] reg_5_out,
    output reg [15:0] reg_6_out,
    output reg [15:0] reg_7_out,
    output reg [15:0] reg_c_out,
    output reg [15:0] reg_s_out,
    output reg [15:0] mux_out
);
    wire [15:0] alu_out;
    wire [2:0] sel;
    wire [2:0] mux_sel;
    wire en_s, en_c, en_0, en_1, en_2, en_3, en_4, en_5, en_6, en_7;




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


    control_unit ctrl_unit (
        .instruction(instruction),
        .run(run),
        .clk(clk),
        .reset(reset),
        .sel(sel),
        .mux_sel(mux_sel),
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



    memory memry(
        .clk(clk),
        .done(done),
        .reset(reset),
        .out(instruction)
    );

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
        .alu_out(alu_out)
    );
endmodule
