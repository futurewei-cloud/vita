import random
import numpy as np
from tqdm import trange
from submodulars import Dummy, Complement


def get_max_subset(submod, S, big_set, k):
    """
    Gets subset of size k that maximizes sum_{u in S}f_u(v) for v in N

    :param submod:
    :param S:
    :param big_set:
    :param k:
    :return: subset
    """

    marginals = []
    for u in big_set:
        marginals.append((u, submod.marginal(S, u)))
    sorted_marginals = sorted(marginals, key=lambda elem: elem[1], reverse=True)
    return set([elem[0] for elem in sorted_marginals[:k]])


def reduce_leq(submod, k):
    """
    Preprocess original universal set so that the size of new set is geq 2k

    :param submod: submodular function
    :param k: k
    :return: new submodular function

    """
    return Dummy(submod, 2 * k), k


def reduce_eq(submod, k):
    """
    Preprocess original universal set so that the size of new set is geq 2k
    :param submod: submodular function
    :param k: k
    :return: new submodular function
    """
    if len(submod) >= 2 * k:
        return submod, k
    else:
        return Complement(submod), len(submod) - k


def wide_size(i, k):
    I = int(np.ceil(0.21 * k))
    if i <= I:
        return 2 * (k - i + 1)
    return k


def random_greedy(submod, k, mode='normal', constraint='eq', seed=None):
    """

    :param submod: Submodular object
    :param k: size of subset constraint
    :param mode: either 'normal' or 'wide'
    :param constraint: either 'leq' or 'eq'
    :return:
    """
    random.seed(seed)
    if mode == 'normal':
        size_fn = lambda i: k
    elif mode == 'wide':
        size_fn = lambda i: wide_size(i, k)
    else:
        raise ValueError('mode is either normal or wide')

    if constraint == 'eq':
        reduce_fn = reduce_eq
    elif constraint == 'leq':
        reduce_fn = reduce_leq
    else:
        raise ValueError('constraint is either "leq" or "eq"')

    return _random_greedy(submod, k, reduce_fn, size_fn)


def _random_greedy(submod, k, reduce_fn, size_fn):
    """
    Runs random greedy algorithm. Assumes 2k <= |N|

    :param submod: non-negative submodular function that takes in a subset of N
    and returns a real value
    :param k: max size of return set (cardinality
    constraint)
    :param size_fn: function that takes in integer and returns a size of
    subset to sample from
    :return: a subset of N, obj(soln)
    """

    submod, k = reduce_fn(submod, k)
    curr_set = set()
    curr_set_comp = submod.universe().copy()
    # for i in range(k):
    for i in trange(k):
        M = get_max_subset(submod, curr_set, curr_set_comp, size_fn(i + 1))
        new_element = random.sample(M, 1)[0]
        curr_set.add(new_element)
        curr_set_comp.remove(new_element)
    approx_obj = submod.eval(curr_set)
    approx_set = submod.unreduce(curr_set)
    return approx_set, approx_obj


