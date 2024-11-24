module branch_logic (
    input wire clk,
    input wire reset,
    input wire [15:0] instruction,
    input wire [15:0] last_alu_result,
    input wire        done,
    output reg [7:0] pc
);

    wire[1:0] format = instruction[1:0];
    wire[1:0] cond = instruction[3:2];
    wire[7:0] immediate = instruction[11:4];

always @(posedge clk) begin
    if (reset) begin
        pc <= 8'd0;
    end else if (done) begin
        if (format == 2'b10) begin
            case (cond)
                2'b00: pc <= (last_alu_result[7:0] == 8'd0) ? immediate : pc + 1; 
                2'b01: pc <= (last_alu_result[7:0] == 8'd1) ? immediate : pc + 1; 
                2'b10: pc <= (last_alu_result[7:0] == 8'd2) ? immediate : pc + 1; 
                default: pc <= pc + 1;
            endcase
        end else begin
            pc <= pc + 1;
        end
    end
end



endmodule
