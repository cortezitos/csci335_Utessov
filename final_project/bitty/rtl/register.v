module register (
    input  wire [15:0] d_in,
    input  wire        reset,
    input  wire        clk,
    input  wire        en,
    output reg  [15:0] d_out
);

    always @(posedge clk) begin
        if (reset) begin
            d_out <= 16'd0;
        end
        else if (en) begin
            d_out <= d_in;
        end
    end

endmodule