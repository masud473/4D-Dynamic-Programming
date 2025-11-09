#include <vector>
#include <algorithm>
#include <climits>

/**
 * @brief Finds the maximum number of chocolates two people can collect on a grid
 *        from (0,0) to (N-1, N-1), moving only Right and Down.
 */
class ChocolatePathFinder {
  public:
  /**
   * @brief Move offsets for Right (k=0) and Down (k=1) movements.
   *        Only indices 0 and 1 are used for the allowed moves.
   */
  int row[4]={0,1,0,-1};
  int col[4]={1,0,-1,0};

    /**
     * @brief Recursive function with memoization to find the maximum collected value
     *        for two people simultaneously moving from (i1, j1) and (i2, j2)
     *        towards the bottom-right corner.
     *
     * @param dp The 4D DP table for memoization: dp[i1][j1][i2][j2].
     * @param mat The N x N grid containing chocolate values.
     * @param i1 Row index of the first person.
     * @param j1 Column index of the first person.
     * @param i2 Row index of the second person.
     * @param j2 Column index of the second person.
     * @param n The size of the grid (N).
     * @return The maximum number of chocolates that can be collected from the
     *         current positions to the end, or INT_MIN if the end is unreachable.
     */
    int travel(std::vector<std::vector<std::vector<std::vector<int>>>>&dp,
               std::vector<std::vector<int>> &mat,
               int i1, int j1, int i2, int j2, int n){
        
        // Base case: both people have reached the destination
        if(i1==n-1 && i2==n-1 && j1==n-1 && j2==n-1) return mat[i1][j1];
        
        // Check memoization table
        if( dp[i1][j1][i2][j2]!=-1) return dp[i1][j1][i2][j2];
        
        int sum=INT_MIN;
        
        // Iterate over the allowed moves for the first person (k=0: Right, k=1: Down)
        for(int k=0;k<2;k++){
            int a=i1+row[k]; // Next row for P1
            int b=j1+col[k]; // Next column for P1
         
            // Iterate over the allowed moves for the second person (l=0: Right, l=1: Down)
            for(int l=0;l<2;l++){
                int c=i2+row[l]; // Next row for P2
                int d=j2+col[l]; // Next column for P2
                
                // Check boundary and obstacle constraints for both new positions
                if(a<n && b<n && c<n && d<n && mat[a][b]!=-1 && mat[c][d]!=-1){
                    // Update maximum collected value from the next step
                    sum=std::max(sum, travel(dp, mat, a, b, c, d, n));
                }
            }
        }
        
        // Store the result for the current state (i1, j1, i2, j2)
        if(sum==INT_MIN){
            // If no path to the end exists from this state
            dp[i1][j1][i2][j2]=INT_MIN;
        } else if(i1==i2 && j1==j2){
            // If both people are on the same cell, collect value only once
            dp[i1][j1][i2][j2]= sum + mat[i1][j1];
        } else {
            // Collect value from both distinct cells
            dp[i1][j1][i2][j2]= sum + mat[i1][j1] + mat[i2][j2];
        }
        
        return dp[i1][j1][i2][j2];
    }
    
    /**
     * @brief Main function to initiate the chocolate collection process.
     * 
     * @param mat The N x N grid where mat[i][j] is the number of chocolates at (i, j),
     *            or -1 if it's an obstacle.
     * @return The maximum number of chocolates that can be collected, or 0 if
     *         the start or end is blocked, or if no path exists.
     */
    int chocolatePickup(std::vector<std::vector<int>> &mat) {
        int n=mat.size();
        
        // Check if the start or end cell is an obstacle
        if(mat[0][0]==-1 || mat[n-1][n-1]==-1) return 0;
        
        // Initialize 4D DP table with -1 (indicating uncalculated states)
        std::vector<std::vector<std::vector<std::vector<int>>>>dp(n,
            std::vector<std::vector<std::vector<int>>>(n,
                std::vector<std::vector<int>>(n,
                    std::vector<int>(n,-1))));
        
        // Start both people at (0, 0)
        int x = travel(dp, mat, 0, 0, 0, 0, (int)mat.size());
        
        // If the max value is INT_MIN, it means the destination is unreachable
        if(x==INT_MIN) return 0;
        
        return x;
    }
};
