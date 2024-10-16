module multiplexer (
    input  wire [15:0] d_in,
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
            4'd0: d_out = reg_0;
            4'd1: d_out = reg_1;
            4'd2: d_out = reg_2;
            4'd3: d_out = reg_3;
            4'd4: d_out = reg_4;
            4'd5: d_out = reg_5;
            4'd6: d_out = reg_6;
            4'd7: d_out = reg_7;
            default: d_out = 16'd0;
        endcase
    end
endmodule
