module ALU (
    input  wire        carry_in,
    input  wire [15:0] in_a,
    input  wire [15:0] in_b,
    input  wire [3:0]  select,
    input  wire        mode,
    output wire        carry_out,
    output wire        compare,
    output wire [15:0]  alu_out
);
    always @(*) begin
        case(mode)
	    1'b0: 
	    1'b1: dfgdf;
        endcase 
    end 






endmodule;

module logic (input wire [15:0] a, input wire [15:0] b, output wire [15:0] alu_out);

    always @(*) begin
        case(select)
            4'b0000: alu_out = ~in_a;
            4'b0001: alu_out = ~(in_a | in_b);
            4'b0010: alu_out = ~in_a & in_b;
            4'b0011: alu_out = 16'd0;
            
        endcase
    end

