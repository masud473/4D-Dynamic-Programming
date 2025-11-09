/**
 * @brief Counts the number of paths from (0, 0) to (n-1, m-1) in a grid
 *        such that the sequence of characters along the path forms a palindrome.
 *        Uses dynamic programming with two simultaneous paths moving towards the middle.
 */
class PalindromicPathCounter {
  public:
    // Modulo value for calculations to prevent overflow.
    int mod=1e9+7;
    
    // Movement directions: (0, 1) Right, (1, 0) Down, (0, -1) Left, (-1, 0) Up.
    // Forward path (k=0, 1) uses Right/Down.
    // Backward path (l=2, 3) uses Left/Up.
    int row[4]={0,1,0,-1};
    int col[4]={1,0,-1,0};

    /**
     * @brief Recursive helper function to count palindromic path segments using DP.
     * 
     * It finds the number of ways two paths can meet in the middle such that 
     * the characters visited by the forward path (i1, j1) match those of the 
     * backward path (i2, j2).
     * 
     * @param dp The 4D DP table: dp[i1][j1][i2][j2] stores the count.
     * @param mat The character matrix/grid.
     * @param i1 Current row of the forward path (starts at 0, 0).
     * @param j1 Current column of the forward path (starts at 0, 0).
     * @param i2 Current row of the backward path (starts at n-1, m-1).
     * @param j2 Current column of the backward path (starts at n-1, m-1).
     * @param n Total number of rows in the matrix.
     * @param m Total number of columns in the matrix.
     * @return The number of palindromic path segments from (i1, j1) and (i2, j2).
     */
    int travel(vector<vector<vector<vector<int>>>> &dp,vector<vector<char>> &mat,int i1,int j1,int i2,int j2,int n,int m){
        // Base case: Paths have crossed/passed each other
        if(i1>i2 ||j1>j2)return 0;
        // Base case: Paths meet at the same cell (middle of an odd length palindrome)
        if(i1==i2 && j1==j2)return 1;
        // Base case: Paths meet at adjacent cells (middle of an even length palindrome)
        if(i1==i2-1 && j1==j2)return 1;
        if(i1==i2 && j1==j2-1)return 1;
        
        // DP memoization check
        if(dp[i1][j1][i2][j2]!=-1)return dp[i1][j1][i2][j2];
        
        int count=0;
        // Iterate over forward path moves (Down/Right, k=0, 1)
        for(int k=0;k<2;k++){
            int a=i1+row[k]; // Next row for forward path
            int b=j1+col[k]; // Next col for forward path

            // Iterate over backward path moves (Up/Left, l=2, 3)
            for(int l=2;l<4;l++){
                int c=i2+row[l]; // Next row for backward path
                int d=j2+col[l]; // Next col for backward path
                
                // Check bounds and palindrome condition (next characters must match)
                if(a<n && b<m && c>=0 && d>=0 && mat[a][b]==mat[c][d]){
                    // Recursive call and sum up results modulo mod
                    count=(count+travel(dp,mat,a,b,c,d,n,m))%mod;
                }
            }
        }
        // Store and return result
        return dp[i1][j1][i2][j2]=count;
    }

    /**
     * @brief Main function to initialize DP and start the counting process.
     * 
     * @param matrix The N x M character grid.
     * @return The total number of valid palindromic paths, modulo 1e9+7.
     */
    int countPalindromicPaths(vector<vector<char>> &matrix) {
        // Code here
        int n=matrix.size(),m=matrix[0].size();
        // Palindrome must start (0,0) and end (n-1, m-1) with the same character.
        if(matrix[0][0]!=matrix[n-1][m-1])return 0; 
        
        // 4D DP table for memoization: dp[r1][c1][r2][c2]
        vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(m, vector<vector<int>>(n, vector<int>(m, -1))));
        
        // Start the two paths: Path 1 at (0, 0), Path 2 at (n-1, m-1)
        return travel(dp,matrix,0,0,n-1,m-1,n,m);
    }
};
