import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;

public class Solution
{
    public String smallestStringWithSwaps(String s, List<List<Integer>> pairs)
    {
        if(pairs.size() == 0)
        {
            return s;
        }

        int len = s.length();
        UnionFind unionFind = new UnionFind(len);
        for(List<Integer> pair : pairs)
        {
            int index1 = pair.get(0);
            int index2 = pair.get(1);
            unionFind.union(index1, index2);
        }

        char[] charArray = s.toCharArray();

        Map<Integer, PriorityQueue<Character> hashMap = new HashMap<>(len);
        for(int i = 0; i < len; i++)
        {
            int root = unionFind.find(i);
            hashMap.computeIfAbsent(root, key->new PriorityQueue<>()).offer(charArray[i]);
        }

        StringBuilder stringBuilder = new StringBuilder();
        for(int i = 0; i < len; i++)
        {
            int root = unionFind.find(i);
            stringBuilder.append(hashMap.get(root).poll());
        }

        return stringBuilder.toString();
    }

    private class UnionFind {
        private int[] parent;

        private int[] rank;

        public UnionFind(int n)
        {
            this.parent = new int[n];
            this.rank = new int[n];
            for(int i = 0; i < n; i++)
            {
                this.parent[i] = i;
                this.rank[i] = 1;
            }
        }

        public void union(int x, int y)
        {
            int rootX = find(x);
            int rootY = find(y);
            if(rootX == rootY)
            {
                return;
            }

            if(rank[rootX] == rank[rootY])
            {
                parent[rootX] = rootY;
                rank[rootY]++;
            }
            else if(rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else
            {
                parent[rootY] = rootX;
            }
        }

        public int find(int x)
        {
            if(x != parent[x])
            {
                parent[x] = find(parent[x]);
            }

            return parent[x];
        }
    }
}