import math

tf_per_file = None
idf = None
pr = None
csv = None
names = None

def init_datasets():
    global tf_per_file
    global idf
    global pr
    global csv
    global names
    f = open("datasets/idf.csv", "r")
    str = f.read()
    list = str.split(',')
    values = list[1::2]
    keys = list[::2]
    idf = dict(zip(keys, values))
    f = open("datasets/pr.csv", "r")
    str = f.read()
    list = str.split(',')
    values = list[1::2]
    keys = list[::2]
    pr = dict(zip(keys, values))
    f = open("datasets/tf.csv", "r")
    names = []
    dicts = []
    readlins = f.readlines()
    for str in readlins:
        list = str.split(',')
        if len(list) == 0: continue
        names.append(list[0])
        del list[0]
        values = list[1::2]
        keys = list[::2]
        tf = dict(zip(keys, values))
        dicts.append(tf)
    
    tf_per_file = dict(zip(names, dicts))

    f = open("datasets/syncategorematic.csv")
    str = f.read() 
    csv = str.split(',')

def search(query):
    q_list = query.lower().split(' ')
    new_list = []
    for i in range(0, len(q_list)):
        if csv.count(q_list[i]) == 0:
            new_list.append(q_list[i])

    total_vals_names = dict()

    for key in tf_per_file:
        total_val = float(0)
        for word in new_list:
            if word in tf_per_file[key]:
                total_val = total_val + (float(tf_per_file[key][word]) / (len(tf_per_file[key]) * len(tf_per_file[key]))) * (float(idf[word]) / (len(tf_per_file) * len(tf_per_file)))

        if key == "\n": 
            continue
        total_val = total_val * float(pr[key])
        total_vals_names[key] = total_val

    print(total_vals_names)

