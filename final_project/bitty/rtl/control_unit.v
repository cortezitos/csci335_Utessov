module control_unit (
    input  wire [15:0] instruction,
    input  wire        run,
    input  wire        clk,
    input  wire        reset,
    output wire  [3:0]  sel,
    output wire  [2:0]  mux_sel,
    output wire         mode,
    output wire         en_s,
    output wire         en_c,
    output wire         en_0,
    output wire         en_1,
    output wire         en_2,
    output wire         en_3,
    output wire         en_4,
    output wire         en_5,
    output wire         en_6,
    output wire         en_7,
    output wire        done
);

    reg [1:0] i = 0;

    always @(posedge clk or posedge reset) begin
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
        end else if (run) begin
            case(i)
                2'd0: begin
                    mux_sel <= instruction[15:13];
                    en_s <= 1;
                    i <= 1;
                end
                2'd1: begin
                    mux_sel <= instruction[12:10];
                    en_c <= 1;
                    sel <= instruction[6:3];
                    mode <= instruction[2];
                    i <= 2;
                end
                2'd2: begin
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
                default: i <= 0;
            endcase
        end
    end

endmodule
