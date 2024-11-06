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
