module memory(
    input  wire         clk,
    input  wire         done,
    input  wire         reset,
    output reg [15:0]  out
);

    reg [2:0] pc = 0; 
    reg [15:0] mem [7:0];

    initial
    $readmemh("rtl/instructions.mem", mem);

    always @(posedge clk) begin
        if (reset) begin
            pc <= 0;
        end
        else if (done) begin
            pc <= pc + 1;
            out <= mem[pc + 1];
        end
        else if (pc == 0) begin
            out <= mem[0];
        end
    end

endmodule
