/*
* //partner: anara32
 * //intro paragraph: countLiveNeighbor function determines how many live cells surround a specific cell by checking all eight potential neighbors, accounting for edge cases
 * //where cells might have fewer than eight neighbors. The updateBoard function applies Conway's Game of Life rules to each cell on the board: a live cell survives with 
 * //2-3 live neighbors and dies otherwise, while a dead cell comes alive with exactly 3 live neighbors. This implementation uses a temporary array to store the next 
 * //generation to prevent changes from affecting subsequent calculations. The aliveStable function checks if the board configuration will change in the next generation
 * //by creating a copy of the board, simulating one update, and comparing the results with the original. This implementation uses a 1D array to represent a 2D board, 
 * //with cell positions calculated as index = row*width + column.
 * 
 * The game uses a 1D array to represent a 2D board. For a cell at row r and column c,
 * its position in the 1D array is calculated as: index = r * boardColSize + c
 * 
*/
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
 int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int liveNeighbors = 0;
    
    // Check all 8 surrounding cells (if they exist)
    for (int i = row - 1; i <= row + 1; i++) {
        // Skip if row is out of bounds
        if (i < 0 || i >= boardRowSize) continue;
        
        for (int j = col - 1; j <= col + 1; j++) {
            // Skip if column is out of bounds
            if (j < 0 || j >= boardColSize) continue;
            
            // Skip the cell itself
            if (i == row && j == col) continue;
            
            // If neighbor is alive, increment counter
            if (board[i * boardColSize + j] == 1) {
                liveNeighbors++;
            }
        }
    }
    
    return liveNeighbors;
}

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    // Create a temporary board to hold the next generation
    // This prevents changes to affect neighbor counts
    int tempBoard[boardRowSize * boardColSize];
    
    // Calculate the next state for each cell
    for (int i = 0; i < boardRowSize; i++) {
        for (int j = 0; j < boardColSize; j++) {
            int index = i * boardColSize + j;
            int neighbors = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);
            
            // Apply Game of Life rules
            if (board[index] == 1) {  // Cell is alive
                if (neighbors < 2 || neighbors > 3) {
                    // Dies due to under/over-population
                    tempBoard[index] = 0;
                } else {
                    // Stays alive
                    tempBoard[index] = 1;
                }
            } else {  // Cell is dead
                if (neighbors == 3) {
                    // Becomes alive due to reproduction
                    tempBoard[index] = 1;
                } else {
                    // Stays dead
                    tempBoard[index] = 0;
                }
            }
        }
    }
    
    // Copy the temporary board back to the original board
    for (int i = 0; i < boardRowSize * boardColSize; i++) {
        board[i] = tempBoard[i];
    }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same
 * as the current step.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    // Create a temporary board to simulate the next generation
    int tempBoard[boardRowSize * boardColSize];
    
    // Copy the original board to the temporary board
    for (int i = 0; i < boardRowSize * boardColSize; i++) {
        tempBoard[i] = board[i];
    }
    
    // Update the temporary board to the next generation
    updateBoard(tempBoard, boardRowSize, boardColSize);
    
    // Compare the original board with the temporary board
    for (int i = 0; i < boardRowSize * boardColSize; i++) {
        if (board[i] != tempBoard[i]) {
            return 0;  // If any cell changed, board is not stable
        }
    }
    
    return 1;  // If all cells remain the same, board is stable
}
