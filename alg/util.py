import numpy as np
import random
import os
import pandas as pd
from typing import Union, Dict
from pathlib import Path



TOP_DIR = os.path.dirname(os.path.realpath(__file__))


def get_stats(fn, num_samples):
    vals = np.array([fn() for _ in range(num_samples)])
    return vals.mean(), vals.max(), vals.std()


def generate_rand_graph(n, m, seed=None):
    """
    Generates a connected graph with n vertices and m edges

    :param n: number of vertices
    :param m: number of edges
    :return: adjacency matrix
    """
    random.seed(seed)
    adj = np.zeros([n, n])
    for v in range(1, n):
        u = random.randint(0, v - 1)
        adj[u, v] = adj[v, u] = random.random()

    num_edges = n - 1
    while num_edges < m:
        u = random.randint(0, n - 1)
        v = random.randint(0, n - 1)
        if u != v and adj[u, v] == 0:
            adj[u, v] = adj[v, u] = random.random()
            num_edges += 1
    return adj


def print_adj(adj):
    n = len(adj)
    for i in range(n):
        print(', '.join((adj[i] > 0).astype(int).astype(str)))

def read_csv(filepath: str, dtype: Union[None, Dict[str, str]] = None) -> pd.DataFrame:
    return pd.read_csv(filepath, sep=',', decimal='.', encoding='utf-8',
                       index_col=None, dtype=dtype)

def write_csv(out_dir: str, df: pd.DataFrame, name: str, create_path: True):
    if create_path:
        Path(out_dir).mkdir(parents=True, exist_ok=True)
    df.to_csv(f'{out_dir}/{name}.csv', mode='w', header=True, index=False)