
def verifyInput(lenAlunos):
    if (not lenAlunos.isdigit()):
        print('Coloque um numero - OBS(Máximo 10) ! ')
        return True
    elif (int(lenAlunos) >= 10):
        print('Numero cadastrado excede o máximo  - OBS(Máximo 10) ! ')
        return True
    return False


def getMenorEntre4(a, b, c, d):
    var = min(a, b, c, d)
    if var == d:
        return True
    if var == c:
        return c
    if var == b:
        return b
    if var == a:
        return a
    return False


def getMedia(a, b, c):
    media = (a+b+c)/3
    if 7 <= media <= 10:
        print('Média :', media)
    elif  0 <= media < 7:
        av4 = float(input("Informe nota Av4: "))
        isLower = getMenorEntre4(a, b, c, av4)
        if isLower is True:
            print("Media inalterada", media)
        else:
            media = (a+b+c+av4-isLower)/3
            print("Nova média:", media)
    else:
        print('undef')
    pass


def calculadora():
    lenAlunos = input(
        'Deseja cadastrar quantos alunos - OBS(Máximo 10) ? ')

    verified = verifyInput(lenAlunos)

    if (verified):
        lenAlunos = input(
            'Deseja cadastrar quantos alunos - OBS(Máximo 10) ? ')     
    opcao = "s"
    loopId = 1
    while loopId < int(lenAlunos)+1 and opcao == "s":
        av1 = float(input("Informe nota Av1: "))
        if(av1 > 10 or av1 < 0):
            av1 = float(input("Informe nota Av1: "))
        av2 = float(input("Informe nota Av2: "))
        av3 = float(input("Informe nota Av3: "))

        getMedia(av1, av2, av3)

        if loopId != int(lenAlunos):
            opcao = (input('Deseja cadastrar novamente S-SIM N-NAO? ')).lower()
        if opcao == "n":
            print('byebye!')
        elif opcao not in ('s','n'):
            opcao = (input('Deseja cadastrar novamente S-SIM N-NAO? ')).lower()
        loopId += 1


def inputable(toInput):
    return input(toInput)
