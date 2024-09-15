module keylock (
    input reset,          // Input reset signal
    input [3:0] key,      // Input key (4-bit to handle numbers 0-9)
    output reg locked     // Output locked signal
);
    // State encoding
    parameter initials = 3'b000;
    parameter first_three = 3'b001;
    parameter second_three = 3'b010;
    parameter five = 3'b011;
    parameter second_two = 3'b100;
    parameter second_five = 3'b101;
    parameter second_six = 3'b110;
    parameter unlock = 3'b111;

    reg [2:0] current_state, next_state;

    // State register (sequential logic)
    always @(*) begin
        if (reset) begin
            current_state <= initials;
        end else begin
            current_state <= next_state;
        end
    end

    // Next state logic (combinational logic)
    always @(key) begin
        case (current_state)
            initials: begin
                if (key == 3) next_state = first_three;
                else next_state = initials;
            end
            first_three: begin
                if (key == 3) next_state = second_three;
                else next_state = initials;
            end
            second_three: begin
                if (key == 5) next_state = five;
                else next_state = initials;
            end
            five: begin
                if (key == 2) next_state = second_two;
                else next_state = initials;
            end
            second_two: begin
                if (key == 5) next_state = second_five;
                else next_state = initials;
            end
            second_five: begin
                if (key == 6) next_state = unlock;
                else next_state = initials;
            end
            unlock: begin
                next_state = unlock;  // Stay in unlock state
            end
            default: begin
                next_state = initials;
            end
        endcase
    end

    // Output logic (combinational logic)
    always @(*) begin
        case (current_state)
            unlock: begin
                locked = 0; // Unlocked
            end
            default: begin
                locked = 1; // Locked
            end
        endcase
    end
endmodule
