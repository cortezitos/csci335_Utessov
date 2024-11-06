module alu (
    input  wire [15:0] in_a,
    input  wire [15:0] in_b,
    input  wire [2:0]  select,
    output reg [15:0] alu_out
);


    always @(*) begin
        case(select)
            3'b000: alu_out = in_a + in_b;
            3'b001: alu_out = in_a - in_b;
            3'b010: alu_out = in_a & in_b;
            3'b011: alu_out = in_a | in_b;
            3'b100: alu_out = in_a ^ in_b;
            3'b101: alu_out = in_a << in_b;
            3'b110: alu_out = in_a >> in_b;
            3'b111: 
                begin
                    if (in_a == in_b) 
                        alu_out = 0;
                    else if (in_a > in_b) 
                        alu_out = 1;
                    else 
                        alu_out = 2;
                end
        endcase

    end

endmodule
