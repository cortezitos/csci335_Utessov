module memory(
    input wire [7:0] pc,
    output reg [15:0]  out,
    output reg       run
);

    reg [15:0] mem [255:0];

    initial
    $readmemh("instructions.mem", mem);

    always @(*) begin
        out = mem[pc];

        if (out == 16'h0020) begin
            run = 0;
        end else begin
            run = 1;
        end
    end

endmodule
