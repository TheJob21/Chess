# Chess
This engine uses algebraic notation for the moves based on FIDE standards. Every legal move can be made now.
I have implemented player vs player, computer vs player, and computer vs computer.
The human vs human part is completed; move validation for every piece, special moves like en passant, castling, and promotions are all in place. Checkmate, stalemate, and regular check seem to work properly. Draws are automatic after 50 moves without capturing a piece or moving a pawn, and a draw will occur after 3 repetitions of the same position on the board.
The computer does not learn, unless I specifically program it. It currently (6/1/2021) plays on Chess.com at a score of around 600-700
