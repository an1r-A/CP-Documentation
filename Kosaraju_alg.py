from collections import defaultdict

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.adj = defaultdict(list)

    def add_edge(self, v, w):
        self.adj[v].append(w)

    def _dfs_util(self, v, visited, stack):
        visited[v] = True
        for neighbor in self.adj[v]:
            if not visited[neighbor]:
                self._dfs_util(neighbor, visited, stack)
        stack.append(v)  # Push vertex to stack on finish

    def _get_transpose(self):
        g = Graph(self.V)
        for v in range(self.V):
            for neighbor in self.adj[v]:
                g.adj[neighbor].append(v)  # Reverse direction of edges
        return g

    def print_sccs(self):
        stack = []
        visited = [False] * self.V

        # Step 1: Fill vertices in stack according to their finishing times
        for i in range(self.V):
            if not visited[i]:
                self._dfs_util(i, visited, stack)

        # Step 2: Create a transposed graph
        transposed_graph = self._get_transpose()

        # Step 3: Perform DFS in the order defined by the stack
        visited = [False] * self.V
        while stack:
            v = stack.pop()
            if not visited[v]:
                transposed_graph._dfs_util(v, visited, [])
                print()  # New line for each SCC

# Example usage
if __name__ == "__main__":
    g = Graph(5)
    g.add_edge(0, 1)
    g.add_edge(1, 2)
    g.add_edge(2, 0)
    g.add_edge(1, 3)
    g.add_edge(3, 4)

    print("Strongly Connected Components are:")
    g.print_sccs()
