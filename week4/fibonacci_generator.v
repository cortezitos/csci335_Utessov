module fibonacci_generator (
    input clk,        // Clock signal
    input rst,        // Synchronous reset
    input enable,     // Enable signal for calculating next Fibonacci number
    output reg [31:0] fib_out  // Output for the current Fibonacci number
);

reg [31:0] fib_prev1;  // F(n-1)
reg [31:0] fib_prev2;  // F(n-2)

always @(posedge clk or posedge rst) begin
    if (rst) begin
        // Initialize Fibonacci numbers
        fib_prev1 <= 32'd1;  // F(1) = 1
        fib_prev2 <= 32'd0; // F(0) = 0
        fib_out <= 32'd0;    // Current Fibonacci number = F(0)
    end else if (enable) begin
        // Compute next Fibonacci number
        fib_out <= fib_prev1 + fib_out;
        
        // Update previous Fibonacci numbers
        fib_prev2 <= fib_prev1;
        fib_prev1 <= fib_out;
    end
end

endmodule
