module control_unit (
    input  wire [15:0] instruction,
    input  wire        run,
    input  wire        clk,
    input  wire        reset,
    output reg  [2:0]  sel,
    output reg  [2:0]  mux_sel,
    output reg         en_s,
    output reg         en_c,
    output reg         en_0,
    output reg         en_1,
    output reg         en_2,
    output reg         en_3,
    output reg         en_4,
    output reg         en_5,
    output reg         en_6,
    output reg         en_7,
    output reg        done
);

    reg [1:0] i = 0;

    always @(posedge clk) begin
        if (reset) begin
            i <= 0;
            en_s <= 0;
            en_c <= 0;
            en_0 <= 0;
            en_1 <= 0;
            en_2 <= 0;
            en_3 <= 0;
            en_4 <= 0;
            en_5 <= 0;
            en_6 <= 0;
            en_7 <= 0;
            done <= 0;
        end else if (run) begin
            case(i)
                2'd0: begin
                    mux_sel <= instruction[15:13];
                    en_s <= 1;
                    i <= 1;
                end
                2'd1: begin
                    en_s <= 0;
                    mux_sel <= instruction[12:10];
                    en_c <= 1;
                    sel <= instruction[4:2];
                    i <= 2;
                end
                2'd2: begin
                    en_c <= 0;
                    case(instruction[15:13])
                        3'd0: en_0 <= 1;
                        3'd1: en_1 <= 1;
                        3'd2: en_2 <= 1;
                        3'd3: en_3 <= 1;
                        3'd4: en_4 <= 1;
                        3'd5: en_5 <= 1;
                        3'd6: en_6 <= 1;
                        3'd7: en_7 <= 1;
                    endcase
                    i <= 0;
                    done <= 1;
                end
                2'd3:begin 
                        en_0 <= 0;
                         en_1 <= 0;
                         en_2 <= 0;
                         en_3 <= 0;
                         en_4 <= 0;
                         en_5 <= 0;
                         en_6 <= 0;
                         en_7 <= 0;
                    end
                default: i <= 0;

            endcase
        end
    end

endmodule
