import random
import time
import numpy as np
import sys
import matplotlib.pyplot as plt

sys.setrecursionlimit(10000000)


def measure_time(func, *args):
    start_time = time.time()
    func(*args)
    end_time = time.time()
    return end_time - start_time


class GRAPH:
    def __init__(self, n):
        self.adj_matrix = np.zeros((n, n), dtype=int)
        self.successors = [[] for _ in range(n)]  # Nastempniki
        self.edges = []
        self.num_vertices = n
        print(sys.getsizeof(self.adj_matrix))

    def add_edge(self, u, v):
        self.adj_matrix[u][v] = 1
        self.successors[u].append(v)
        self.edges.append((u, v))

    def generate_matrix_your_self(self):
        n = self.adj_matrix.shape[0]
        print("Make Matrix: ")
        for r in range(n):
            for c in range(n):
                u, v = int(input(f"Enter element [{r},{c}]: "))
                self.add_edge(u, v)

    def generate_graph(self):
        n = self.adj_matrix.shape[0]
        for i in range(n):
            for j in range(i +5, n):
                self.add_edge(i, j)

    def print_adj_matrix(self):
        print("Adjacency matrix:")
        print(self.adj_matrix)

    def print_nastempniki(self):
        print("Successors:")
        for i, s in enumerate(self.successors):
            print(f"{i}: {s}")

    def print_krawendzi(self):
        print("Edges:")
        for u, v in self.edges:
            print(f"{u} -> {v}")

    def BFS(self):
        start_node = 1
        visited = [False] * self.num_vertices
        queue = [start_node]
        visited[start_node] = True

        while queue:
            node = queue.pop(0)
            print(node, end=" ")

            for i in range(self.num_vertices):
                if self.adj_matrix[node, i] == 1 and not visited[i]:
                    visited[i] = True
                    queue.append(i)

    def DFS(self):
        visited = [False] * self.num_vertices
        start_node = 0

        def traverse(node):
            visited[node] = True
            print(node, end=" ")

            for i in range(self.num_vertices):
                if self.adj_matrix[node, i] == 1 and not visited[i]:
                    traverse(i)

        traverse(start_node)

    def topological_sort_dfs_Nastemp(self):
        WHITE, GRAY, BLACK = 0, 1, 2  # WHITE не посещенная, GRAY посещаемая, BLACK посещенная

        color = [WHITE] * self.num_vertices
        sorted_vertices = []

        def dfs(node):
            color[node] = GRAY
            for successor in self.successors[node]:  # Dla każdego sąsiada wierzchołka
                if color[successor] == WHITE:
                    dfs(successor)  # Rekurencyjnie odwiedzamy sąsiada
            sorted_vertices.append(node)  # Dodajemy wierzchołek na stos

        for node in range(len(self.successors)):  # Dla każdej nieodwiedzonej wierzchołka
            if color[node] == WHITE:
                dfs(node)  # Uruchamiamy DFS od niej

        return sorted_vertices[::-1]

    def topological_sort_bfs_Nastemp(self):

        in_degrees = [0] * self.num_vertices
        sorted_vertices = []
        queue = []

        for u in range(self.num_vertices):
            for successor in self.successors[u]:
                in_degrees[successor] += 1

        for u in range(self.num_vertices):
            if in_degrees[u] == 0:
                queue.append(u)

        while queue:
            u = queue.pop(0)
            sorted_vertices.append(u)
            for successor in self.successors[u]:
                in_degrees[successor] -= 1
                if in_degrees[successor] == 0:
                    queue.append(successor)

        print("Topological order (BFS):")
        print(sorted_vertices)

    def topological_sort_dfs_sasiedztwa(self):
        WHITE, GRAY, BLACK = 0, 1, 2  # WHITE не посещенная, GRAY посещаемая, BLACK посещенная

        color = [WHITE] * self.adj_matrix.shape[0]
        sorted_vertices = []

        def visit(u):
            color[u] = GRAY
            for v in range(self.adj_matrix.shape[0]):
                if self.adj_matrix[u][v] == 1 and color[v] == WHITE:
                    visit(v)
            color[u] = BLACK

            sorted_vertices.append(u)

        for u in range(self.adj_matrix.shape[0]):
            if color[u] == WHITE:
                visit(u)

        sorted_vertices.reverse()
        print("Topological order (DFS):")
        print(sorted_vertices)

    def topological_sort_bfs_sasiedztwa(self):

        in_degree = [0] * self.adj_matrix.shape[0]
        sorted_vertices = []
        queue = []
        for u in range(self.adj_matrix.shape[0]):
            for v in range(self.adj_matrix.shape[1]):
                if self.adj_matrix[v][u] == 1:
                    in_degree[u] += 1

        for u in range(self.adj_matrix.shape[0]):
            if in_degree[u] == 0:
                queue.append(u)

        while queue:
            u = queue.pop(0)
            sorted_vertices.append(u)
            for v in range(self.adj_matrix.shape[0]):
                if self.adj_matrix[u][v] == 1:
                    in_degree[v] -= 1
                    if in_degree[v] == 0:
                        queue.append(v)

        print("Topological order (BFS):")
        print(sorted_vertices)

    def topological_sort_dfs_edges(self):
        WHITE, GRAY, BLACK = 0, 1, 2

        color = [WHITE] * self.num_vertices
        sorted_vertices = []

        def dfs(node):
            color[node] = GRAY
            for (u, v) in self.edges:
                if u == node and color[v] == WHITE:
                    dfs(v)
            sorted_vertices.append(node)

        for vertex in range(self.num_vertices):
            if color[vertex] == WHITE:
                dfs(vertex)

        return sorted_vertices[::-1]
    def topological_sort_bfs_edges(self):
        in_degrees = [0] * self.num_vertices
        sorted_vertices = []
        queue = []

        for u, v in self.edges:
            in_degrees[v] += 1

        for u in range(self.num_vertices):
            if in_degrees[u] == 0:
                queue.append(u)

        while queue:
            u = queue.pop(0)
            sorted_vertices.append(u)
            for e, s in self.edges:
                if e == u:
                    in_degrees[s] -= 1
                    if in_degrees[s] == 0:
                        queue.append(s)

        print("Topological order edge (BFS):")
        print(sorted_vertices)





def TimeConsumingGraphAlgorithm(n_values: list):
    adj_matrix_timea = []
    successors_timea = []
    edges_timea = []
    dfs_timea = []
    bfs_timea = []
    dfs_topo_timea = []
    bfs_topo_timea = []
    dfs_topo_timea_N = []
    bfs_topo_timea_N = []
    bfs_topo_timea_Kraw = []
    dfs_topo_timea_Kraw = []
    for n in n_values:
        graph = GRAPH(n)

        adj_matrix_time = measure_time(graph.generate_graph)
        adj_matrix_timea.append([adj_matrix_time, n])

        successors_time = measure_time(graph.print_nastempniki)
        successors_timea.append([successors_time, n])

        edges_time = measure_time(graph.print_krawendzi)
        edges_timea.append([edges_time, n])

        dfs_time = measure_time(graph.DFS)
        dfs_timea.append([dfs_time, n])

        bfs_time = measure_time(graph.BFS)
        bfs_timea.append([bfs_time, n])

        dfs_topo_time = measure_time(graph.topological_sort_dfs_sasiedztwa)
        dfs_topo_timea.append([dfs_topo_time, n])

        bfs_topo_time = measure_time(graph.topological_sort_bfs_sasiedztwa)
        bfs_topo_timea.append([bfs_topo_time, n])

        dfs_topo_timea_N.append([measure_time(graph.topological_sort_dfs_Nastemp), n])
        bfs_topo_timea_N.append([measure_time(graph.topological_sort_bfs_Nastemp), n])

        dfs_topo_timea_Kraw.append([measure_time(graph.topological_sort_dfs_edges), n])
        bfs_topo_timea_Kraw.append([measure_time(graph.topological_sort_bfs_edges), n])

    # Create the x and y values for the graph
    x_values = [n[0] for n in adj_matrix_timea]
    y_values = [n[1] for n in adj_matrix_timea]

    # Create the graph using Matplotlib
    # plt.plot(x_values, y_values, label="2X2_time")

    # plt.plot([n[0] for n in successors_timea], [n[1] for n in successors_timea], label="successors")

    # plt.plot([n[0] for n in edges_timea], [n[1] for n in edges_timea], label="edges")

    plt.plot([n[0] for n in dfs_timea], [n[1] for n in dfs_timea], label="dfs_time")
    plt.plot([n[0] for n in bfs_timea], [n[1] for n in bfs_timea], label="bfs_time")

    plt.plot([n[0] for n in dfs_topo_timea], [n[1] for n in dfs_topo_timea], label="dfs_topo_time_Sasiedstwa")
    plt.plot([n[0] for n in bfs_topo_timea], [n[1] for n in bfs_topo_timea], label="bfs_topo_time_Sasiedstwa")

    plt.plot([n[0] for n in dfs_topo_timea_N], [n[1] for n in dfs_topo_timea_N], label="dfs_topo_time_Nastem")
    plt.plot([n[0] for n in bfs_topo_timea_N], [n[1] for n in bfs_topo_timea_N], label="bfs_topo_time_Nastem")

    plt.plot([n[0] for n in dfs_topo_timea_Kraw], [n[1] for n in dfs_topo_timea_Kraw], label="dfs_topo_time_Kraw")
    plt.plot([n[0] for n in bfs_topo_timea_Kraw], [n[1] for n in bfs_topo_timea_Kraw], label="bfs_topo_time_Kraw")

    # Add labels to the graph
    plt.title('Graph')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.legend()
    # Display the graph
    plt.show()


if __name__ == '__main__':
    while True:
        print("Menu:")
        print("1. Wygeneruj graf ze  1/2 krawędziami")
        print("2. Wygeneruj graf z macierzą sąsiedztwa osobiscie")
        print("3. Wyświetl macierz sąsiedztwa")
        print("4. Wyświetl następniki")
        print("5. Wyświetl krawędzie")
        print("6. Przeprowadź przechodzenie BFS")
        print("7. Przeprowadź przechodzenie DFS")
        print("8. Przeprowadź sortowanie topologiczne za pomocą DFS (następniki)")
        print("9. Przeprowadź sortowanie topologiczne za pomocą BFS (następniki)")
        print("10. Przeprowadź sortowanie topologiczne za pomocą DFS (S)")
        print("11. Przeprowadź sortowanie topologiczne za pomocą BFS (S)")
        print("12. Time")
        print("13. Exit")
        choice = input("Wybierz opcję: ")

        if choice == "1":
            n = int(input("Podaj liczbę wierzchołków: "))
            graf = GRAPH(n)
            graf.generate_graph()


        elif choice == "2":
            n = int(input("Podaj liczbę wierzchołków: "))
            graf = GRAPH(n)
            graf.generate_matrix_your_self()

        elif choice == "3":
            graf.print_adj_matrix()

        elif choice == "4":
            graf.print_nastempniki()

        elif choice == "5":
            graf.print_krawendzi()

        elif choice == "6":
            graf.BFS()

        elif choice == "7":
            graf.DFS()

        elif choice == "8":
            print(graf.topological_sort_dfs_Nastemp())

        elif choice == "9":
            print(graf.topological_sort_bfs_Nastemp())

        elif choice == "10":
            graf.topological_sort_dfs_sasiedztwa()

        elif choice == "11":
            graf.topological_sort_bfs_sasiedztwa()

        elif choice == "12":
            TimeConsumingGraphAlgorithm([100, 150 , 200, 300, 400,  600, 700,  900, 1000,1250 , 1600])

        elif choice == "13":
            break

        elif choice == "14":
            print(graf.topological_sort_dfs_edges())
            print(graf.topological_sort_bfs_edges())
        else:
            print("Nieprawidłowa opcja, spróbuj ponownie.")
