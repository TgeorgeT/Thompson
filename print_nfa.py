import matplotlib.pyplot as plt
import networkx as nx

g = nx.DiGraph()

with open('transitions.txt') as f:
    lines = [line.strip().split() for line in f.readlines()]

for line in lines:
    g.add_node(line[0].split(':')[0])

for line in lines:
    for i in range(1, len(line)):
        weight = line[i].split(',')[0][1:]
        if weight == '_':
            weight = 'λ'
        dest = line[i].split(',')[1][:-1]
        g.add_edge(line[0].split(':')[0], dest, label=weight)

pos = nx.spring_layout(g)

# Draw the graph
nx.draw(g, pos, with_labels=True, node_size=700)

# Create a dictionary of edge labels
edge_labels = nx.get_edge_attributes(g, 'label')

# Draw edge labels
nx.draw_networkx_edge_labels(g, pos, edge_labels=edge_labels)

plt.show()