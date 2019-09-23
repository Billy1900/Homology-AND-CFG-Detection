import multiprocessing
from CFG import CFG
from HomologyDetection import homologyDetection

def multiprocess():
    pool = multiprocessing.Pool()
    result = []

    result.append(pool.apply_async(CFG).get())
    result.append(pool.apply_async(homologyDetection).get())

    pool.close()
    return result

