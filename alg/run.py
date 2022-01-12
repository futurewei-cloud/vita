from submodulars import Cut
from algorithms.random_greedy import random_greedy
from algorithms.brute_force import brute_force
from util import *
import networkx as nx
import matplotlib.pyplot as plt
import math
from pandas.core.frame import DataFrame

def main():
    # graph_seed = 123
    graph_seed = None
    algo_seed = None
    num_samples = 100

    # k = 10
    # n = 2 * k
    # m = int(k ** 1.5)
    # adj = generate_rand_graph(n, m, seed=graph_seed)
    adj = read_csv("./input/vpcnode.csv")
    cut_submod = Cut(adj)

    mode = 'normal'
    constraint = 'leq'
    print('Running Random Greedy')
    # approx_val = get_mean(lambda: random_greedy(cut_submod, k, mode, constraint,
    #                                             seed=algo_seed)[1], num_samples)

    print('Running Brute Force\n')
    opt = 15.066
    lower = opt * (1 - 1 / math.e)
    # opt = brute_force(cut_submod, k, constraint)
    print('Approx OBJ:', approx_val)
    print('OPT:', opt)
    print('Lower bound:', lower)
    approx_set, _ = random_greedy(cut_submod, k, mode, constraint,
                                  seed=algo_seed)
    # print_adj(adj)
    g = nx.from_numpy_matrix(adj)
    div = g
    for s in div:
        if approx_set.issubset(s):
            div.append(approx_set)
            div.append(list(set(s).difference_update(set(approx_set))))
    res = DataFrame(div)
    write_csv("./output",res,"random_greedy")


if __name__ == '__main__':
    main()