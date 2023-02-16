/**
This convex hull solution is shorter because it uses a simpler algorithm known as the Graham scan algorithm. 
The algorithm starts by sorting the points in ascending order of their polar angle with respect to a fixed point, called the pivot point.
Then, it scans the points in this order and keeps a stack of the points that form the convex hull. At each step, 
it checks whether the current point makes a left turn or a right turn with respect to the last two points in the stack.
If it makes a left turn, it adds the point to the stack. 
If it makes a right turn, it removes the top point from the stack until the current point makes a left turn with respect to the last two points in the stack.

The solution you provided is using a deque to implement the Graham scan algorithm. 
The cross product is used to determine whether a point makes a left turn or a right turn with respect to the last two points in the deque. 
The set is used to remove any duplicates in the convex hull that may have been introduced during the algorithm. 
Overall, this solution is shorter and easier to understand than the original code 
because it uses a simpler algorithm and a more concise implementation.
 */
class Solution  {
public:
    using tree = vector<int>;
    int cross(tree& B, tree& A, tree& T){
        return (T[1]-B[1])*(B[0]-A[0]) - (B[1]-A[1])*(T[0]-B[0]);
    }
    vector<tree> outerTrees(vector<tree>& trees)  {
        sort(trees.begin(), trees.end());
        deque<tree> F;
        for (tree T : trees) {
            while (F.size() >= 2 and cross(F[F.size()-1],F[F.size()-2],T) < 0)
                F.pop_back();
            F.push_back(T);

            while (F.size() >= 2 and cross(F[0],F[1],T) > 0)
                F.pop_front();
            F.push_front(T);
        }
        set<tree> unique(F.begin(), F.end());
        return vector<tree>(unique.begin(), unique.end());
    }
};