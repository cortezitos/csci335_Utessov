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
	    1'b0: arithmetic a (select, in_a, in_b, alu_out)
	    1'b1: logic l(select, in_a, in_b, alu_out);
        endcase 
    end 






endmodule;

module logic (
    input wire [3:0] select, 
    input wire [15:0] A, B, 
    output wire [15:0] alu_out);

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
    output wire [15:0] alu_out     
);

always @(*) begin
    case (select)
        4'b0000: alu_out = A;                
        4'b0001: alu_out = A | B;           
        4'b0010: alu_out = A | ~B;          
        4'b0011: alu_out = -1;               
        4'b0100: alu_out = A | (A & ~B);     
        4'b0101: alu_out = (A | B) + (A & ~B); 
        4'b0110: alu_out = A - B - 1;       
        4'b0111: alu_out = (A & ~B) - 1;     
        4'b1000: alu_out = A + (A & B);      
        4'b1001: alu_out = A + B;           
        4'b1010: alu_out = (A | B) + (A & B); 
        4'b1011: alu_out = (A & B) - 1;      
        4'b1100: alu_out = A + A;           
        4'b1101: alu_out = (A | B) + (A & ~B); 
        4'b1110: alu_out = (A | B) + (A & B); 
        4'b1111: alu_out = A - 1;          
        default: alu_out = 1'b0;            
    endcase
end

endmodule
