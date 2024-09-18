module alu (
    input              clk,
    input              rst,
    input  wire        carry_in,
    input  wire [15:0] in_a,
    input  wire [15:0] in_b,
    input  wire [3:0]  select,
    input  wire        mode,
    output wire        carry_out,
    output wire        compare,
    output wire [15:0]  alu_out
);

    
    wire reg [15:0] logic_out, arithmetic_out;
    wire reg arithmetic_carry_out;

    logik l0 (
        .select(select),
        .A(in_a),
        .B(in_b),
        .alu_out(logic_out)
    );

    arithmetic a0 (
        .select(select),
        .A(in_a),
        .B(in_b),
        .carry_in(carry_in),
        .carry_out(arithmetic_carry_out),
        .alu_out(arithmetic_out)
    );

    assign alu_out = (mode == 1) ? logic_out : arithmetic_out;
    assign carry_out = (mode == 1) ? arithmetic_carry_out : 1'b0;
    assign compare = (in_a == in_b);






endmodule;

module logik (
    input wire [3:0] select, 
    input wire [15:0] A, B, 
    output reg [15:0] alu_out);

    always @(*) begin
        case(select)
            4'b0000: alu_out = ~A;
            4'b0001: alu_out = ~(A | B);
            4'b0010: alu_out = ~A & B;
            4'b0011: alu_out = 16'h0000;
            4'b0100: alu_out = ~(A & B);
            4'b0101: alu_out = ~B;
            4'b0110: alu_out = A ^ B;
            4'b0111: alu_out = A & ~B;
            4'b1000: alu_out = ~A | B;
            4'b1001: alu_out = ~(A ^ B);
            4'b1010: alu_out = B;
            4'b1011: alu_out = A & B;
            4'b1100: alu_out = 16'hFFFF; 
            4'b1101: alu_out = A | ~B;
            4'b1110: alu_out = A | B;
            4'b1111: alu_out = A;
            default: alu_out = 16'h0000;  
            
        endcase
    end
endmodule

module arithmetic (
    input wire [3:0] select,    
    input wire [15:0] A, B,            
    input wire carry_in,        
    output reg carry_out,   
    output reg [15:0] alu_out    
);

always @(*) begin
    case (select)
        4'b0000: alu_out = A;
        4'b0001: alu_out = A | B;
        4'b0010: alu_out = A | ~B;
        4'b0011: alu_out = -1;
        4'b0100: alu_out = A | (A & ~B);
        4'b0101: {carry_out, alu_out} = {1'b0, (A | B)} + {1'b0, (A & ~B)};
        4'b0110: alu_out = A - B - 1;
        4'b0111: alu_out = (A & ~B) - 1;
        4'b1000: {carry_out, alu_out} = {1'b0, A} + {1'b0, (A & B)};
        4'b1001: {carry_out, alu_out} = {1'b0, A} + {1'b0, B};
        4'b1010: {carry_out, alu_out} = {1'b0, (A | ~B)} + {1'b0, (A & B)};
        4'b1011: alu_out = (A & B) - 1;
        4'b1100: {carry_out, alu_out} = {1'b0, A} + {1'b0, A};
        4'b1101: {carry_out, alu_out} = {1'b0, (A | B)} + {1'b0, A};
        4'b1110: {carry_out, alu_out} = {1'b0, (A | ~B)} + {1'b0, A};
        4'b1111: alu_out = A - 1;
        default: alu_out = 16'b0;
    endcase
end

endmodule
