module alu (
    input  wire [15:0] in_a,
    input  wire [15:0] in_b,
    input  wire [3:0]  select,
    input  wire        mode,
    output reg        carry_out,
    output reg        compare,
    output reg [15:0] alu_out
);


    always @(*) begin
        case(mode)
            1'b0: 
            begin
                carry_out = 0;  
                case (select)
                    4'b0000: alu_out = in_a;
                    4'b0001: alu_out = in_a | in_b;
                    4'b0010: alu_out = in_a | ~in_b;
                    4'b0011: alu_out = -1;
                    4'b0100: alu_out = in_a | (in_a & ~in_b);
                    4'b0101: {carry_out, alu_out} = {1'b0, (in_a | in_b)} + {1'b0, (in_a & ~in_b)};
                    4'b0110: alu_out = in_a - in_b - 1;
                    4'b0111: alu_out = (in_a & ~in_b) - 1;
                    4'b1000: {carry_out, alu_out} = {1'b0, in_a} + {1'b0, (in_a & in_b)};
                    4'b1001: {carry_out, alu_out} = {1'b0, in_a} + {1'b0, in_b};
                    4'b1010: {carry_out, alu_out} = {1'b0, (in_a | ~in_b)} + {1'b0, (in_a & in_b)};
                    4'b1011: alu_out = (in_a & in_b) - 1;
                    4'b1100: {carry_out, alu_out} = {1'b0, in_a} + {1'b0, in_a};
                    4'b1101: {carry_out, alu_out} = {1'b0, (in_a | in_b)} + {1'b0, in_a};
                    4'b1110: {carry_out, alu_out} = {1'b0, (in_a | ~in_b)} + {1'b0, in_a};
                    4'b1111: alu_out = in_a - 1;
                    default: alu_out = 16'b0;
                endcase
            end

            1'b1: 
            begin
                case(select)
                    4'b0000: alu_out = ~in_a;
                    4'b0001: alu_out = ~(in_a | in_b);
                    4'b0010: alu_out = ~in_a & in_b;
                    4'b0011: alu_out = 16'h0000;
                    4'b0100: alu_out = ~(in_a & in_b);
                    4'b0101: alu_out = ~in_b;
                    4'b0110: alu_out = in_a ^ in_b;
                    4'b0111: alu_out = in_a & ~in_b;
                    4'b1000: alu_out = ~in_a | in_b;
                    4'b1001: alu_out = ~(in_a ^ in_b);
                    4'b1010: alu_out = in_b;
                    4'b1011: alu_out = in_a & in_b;
                    4'b1100: alu_out = 16'hFFFF; 
                    4'b1101: alu_out = in_a | ~in_b;
                    4'b1110: alu_out = in_a | in_b;
                    4'b1111: alu_out = in_a;
                    default: alu_out = 16'h0000; 
                endcase
            end
        endcase
        compare = (in_a == in_b) ? 1 : 0;
    end

endmodule
