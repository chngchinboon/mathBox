import numpy as np
from itertools import product

def binary(bits=2):
    #result = ["".join(seq) for seq in product("01", repeat=bits)]
    result = [np.asarray(seq,dtype=int) for seq in product("01", repeat=bits)]

    return result

#args0,args1,digit0,digit1,tries0,tries1,add,minus,multi,divide

def genargs(opsval, ops, args, digits, allowneg):
    #print('Generating argument list')
    #argsval = np.random.randint(0, 10**digits-1,args)

    argsval = [None]*args
    if ops[0] == 1: #divide present. need to handle
        #proposed force query into single digit divides. replace number of args & operators
        pass
    else:
        argsval[0] = np.random.randint(0, 10 ** digits - 1)

        for i in range(args-1):
            #get candidate 2nd arg
            if allowneg == 1:
                argsval[i+1] = np.random.randint(0, 10 ** digits - 1)
            else:
                acceptable = 0
                regen = 0
                while acceptable == 0 :
                    argsval[i+1] = np.random.randint(0, 10 ** digits - 1)
                    testeval = calcuwithop(argsval[i],opsval[i],argsval[i+1])
                    acceptable = checkforneg(testeval)

                    if regen == 10:
                        #possibly first argument is too small. regenerate first argument
                        argsval[i] = np.random.randint(0, 10 ** digits - 1)
                        regen = 0
                        print('Regen first arg')
                    regen += 1

    return argsval

def checkforneg(result):
    if result >0:
        acceptable = 1
    else:
        acceptable = 0
    return acceptable

def calcuwithop(arg1, op, arg2):
    if op == 1: # divide
        result = arg1 / arg2
    elif op == 2: # multiply
        result = arg1 * arg2
    elif op == 3:  # add
        result = arg1 + arg2
    elif op == 4:  # minus
        result = arg1 - arg2
    print(arg1,op,arg2,result)
    return result

def crawlargop(argsval, args, opsval, respectorder):
    ops = args - 1
    if respectorder==1:
        for i in range(args):
            if i == 0:
                result = argsval[0]
            else:
                result = calcuwithop(result,opsval[i-1],argsval[i])
    else:#have to deal with multiply or divide piority
        #generate temp array to store processed status
        #0 unprocessed
        #1 priority
        #2 used
        opstatus = [0]*ops

        iteration = 0

        while sum(opstatus)<ops:
            #print('Iteration:{}'.format(iteration))
            fprior = 0
            for j in range(ops): #m & d
                if (opsval[j] == 1 or opsval[j] == 2) and opstatus[j] == 0:
                    if iteration == 0:
                        result = calcuwithop(argsval[j], opsval[j], argsval[j + 1])  # check if has multiply or divide
                    else:
                        result = calcuwithop(result, opsval[j], argsval[j + 1])  # check if has multiply or divide
                    opstatus[j] = 1
                    fprior = 1
                break

            if fprior == 1:
                iteration += 1
                continue

            for j in range(ops):
                if opstatus[j] == 0:
                    if iteration == 0:
                        result = calcuwithop(argsval[j], opsval[j], argsval[j + 1])  # check if has multiply or divide
                    else:
                        result = calcuwithop(result, opsval[j], argsval[j + 1])
                    opstatus[j] = 1
                    break

            iteration += 1

    return result
'''
            if iteration == 0: # first pass check if query has divide/multiply and mark for processing
                for j in range(ops):
                    if opval[j] == 1 or opval[j] == 2:
                        opstatus[j] = 1
            else: # start processing

                for j in range(ops):
                    if (opval[j] == 1 or opval[j] == 2) and opstatus[j] == 1:
                        if i == 1: #handle first
                            result = calcuwithop(argval[j], opval[j], argval[j + 1])# check if has multiply or divide

                    elif (opval[j] == 1 or opval[j] == 2) and opstatus[j] == 0:
                        result = calcuwithop(result, opval[j], argval[j+1])
            opstatus[j] = 1
            
'''



def genops(add,minus,multi,divide):
    ops = [1, 2, 3, 4]
    ops[0] *= divide
    ops[1] *= multi
    ops[2] *= add
    ops[3] *= minus

    return ops

def genopsval(ops,args):
    #print('Generating operator list')
    #python only
    opsval = [0 for i in range(args-1)]
    for i in range(args-1):
        while opsval[i] == 0 or opsval[i] == 1:#skip divide
            opsval[i] = np.random.choice(ops)

    return opsval

def getans(argsval, args, opsval):
    ans=0
    for idx in range(args):
        if idx == 0:
            ans = argsval[idx]
        else:
            if opsval[idx-1] == 1:#divide
                print('Divide found. Skipping')
                #pass

            elif opsval[idx-1] == 2: # multiply
                ans *= argsval[idx]
            elif opsval[idx - 1] == 3:  # add
                ans += argsval[idx]
            elif opsval[idx - 1] == 4:  # minus
                ans -= argsval[idx]

    return ans

def genquery(args0,args1,digit0,digit1,tries0,tries1,add,minus,multi,divide):

    #### python only
    args = args1 * 2 + args0 + 2
    print('Args: #{}'.format(args))
    digits = digit1 * 2 + digit0 + 1
    print('Digits: #{}'.format(digits))
    tries = tries1 * 2 + tries0 + 1
    print('Tries: #{}'.format(tries))
    opsdict={1:'/',2:'*',3:'+',4:'-'}
    ####

    ops = genops(add,minus,multi,divide)
    opsval = genopsval(ops,args)
    argsval = genargs(opsval,ops,args, digits,allowneg=0)

    ####python only
    # convert to strings
    argsstr = [str(i) for i in argsval]
    opsstr = [opsdict[i] for i in opsval]
    query = [None] * (len(argsstr) + len(opsstr))
    query[::2] = argsstr
    query[1::2] = opsstr


    # In future to comply with order of operations
    '''
    query=[None] * (len(argsstr) + 2*len(opsstr))
    query[0]="("*(args-2)
    query[1]=argsstr[0]
    query[3::3]=argsstr[1:]
    query[2::3] = opsstr
    query[4::3] = [')']*len(query[5::3])
    '''

    query =  " ".join(query + ['='])
    print('Query: {}'.format(query))

    #getanswer
    ans=getans(argsval,opsval)

    ####python only
    print('Answer: {}'.format(ans))
    print('Full string: {} {}'.format(query,ans))
    ####

    return argsval, opsval, ops, tries, query, ans

#args0,args1,digit0,digit1,tries0,tries1,add,minus,multi,divide
'''
test = binary(10)
idx = np.random.randint(0,1024,5)
result=[]
for i in idx:
    print('###### Test {} ######'.format(i))
    result.append(genquery(*test[i]))
    print('')
'''
result=[]
for i in range(5):
    print('###### Test {} ######'.format(i))
    result.append(genquery(0,0,1,0,1,1,0,1,0,0))
    print('')



