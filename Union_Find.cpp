// int might have to be an ll
// rank could be used instead of size (rank is actually better)

class UnionFind {
    public:
        vector<ll> size, sets;
        UnionFind(int n) {
            sets.assign(n, 0);
            for(int i = 0; i < n; ++i) sets[i] = i;
            size.assign(n, 1);
        }
        int parent(int i) {
            if(sets[i] == i)
                return i;
            return parent(sets[i]);
        }
        bool inSameSet(int i, int j) {
            return parent(i) == parent(j); 
        } 
        void unite(int i, int j) {
            if (inSameSet(i, j)) return; 
            
            int x = parent(i);
            int y = parent(j);

            if(size[x] < size[y]) {
                int tmp = x;
                x = y;
                y = tmp;
            }
                
            sets[y] = x;
            size[x] += size[y];
        }
};
