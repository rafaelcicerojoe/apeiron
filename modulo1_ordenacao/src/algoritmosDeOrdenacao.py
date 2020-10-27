import time
import numpy

'''
Introdução:
- Implementar algoritmo de ordenação que receba uma colecão
- A coleção é uma lista de arestas
- Para comparar o peso as arestas entre dois item da coleção basta usar a chave 'weight' (peso)
Exemplos:
- Modo convencional
colecao[i] operador de comparacao colecao[j]
colecao[i] < colecao[j]
- Modo que você vai usar
int(colecao[i]['weight']) operador de comparacao int(colecao[j]['weight'])
int(colecao[i]['weight']) < int(colecao[j]['weight'])
É nescessário converter o valor pra Interger no momento da comparação a fim de evitar erros
'''


class QuickSort(object):
    def ordenar(self, colecao):
        init = float(time.time())

        self.quick(colecao, 0, len(colecao) - 1)

        end = float(time.time())
        print(end - init)

        return colecao

    def quick(self, colecao, esq, dir):
        i = esq
        j = dir
        #Delimitação do lado do "vetor" a ser usado no ordenamento
        col = colecao[esq + (dir - esq) // 2] # Pivô ( variavel Key) com uma melhor posiçao -- ao meio --
        while i <= j:
            while int(colecao[i]['weight']) < int(col['weight']):
                i += 1
            while int(colecao[j]['weight']) > int(col['weight']):
                j -= 1

            if i <= j:
                colecao[i], colecao[j] = colecao[j], colecao[i]
                i += 1
                j -= 1
        #Distribuiçao para aplicação ao "menor" particionamento
        if esq < j:
            self.quick(colecao, esq, j)

        if i < dir:
            self.quick(colecao, i, dir)

        return colecao


class MergeSort(object):
    def ordenar(self, colecao):
        init = float(time.time())

        self.merge(colecao)

        end = float(time.time())
        print(end - init)

        return colecao

    def merge(self, colecao):
        if len(colecao) > 1:
            meio = int(len(colecao) // 2)
            E = colecao[:meio]
            D = colecao[meio:]
            # Divide-se a estrutura
            self.merge(E)
            self.merge(D)

            i = 0
            j = 0
            k = 0

            # Copia dado para colecao de E[] e D[]
            while i < len(E) and j < len(D):
                if int(E[i]['weight']) < int(D[j]['weight']):
                    colecao[k] = E[i]
                    i += 1
                else:
                    colecao[k] = D[j]
                    j += 1
                k += 1
            # Verifica se resta algum elemento a ser ordenado
            while i < len(E):
                colecao[k] = E[i]
                i += 1
                k += 1

            while j < len(D):
                colecao[k] = D[j]
                j += 1
                k += 1
        return colecao


class InsertSort(object):
    def ordenar(self, colecao):
        init = float(time.time())
        for i in range(1, len(colecao)):
            # Ordena linearmente comparando e trocando de acordo com a ordem
            key = colecao[i]
            j = i - 1
            while j >= 0 and int(key['weight']) < int(colecao[j]['weight']):
                colecao[j + 1] = colecao[j]
                j -= 1
            colecao[j + 1] = key
        end = float(time.time())
        print(end - init)
        return colecao


# Comparação interna com insert feitas por shell e select

# Casos especiais parcial e final -- Insert default [Digite 1] nos Finais -- Shell default [Digite algo maior que 2] nos parciais

class MergeSortParcial(object):
    def ordenar(self, colecao):

        L = int(input('Digite um tamanho L :\n'))
        ID = int(input('\nDigite um ID >>>> (1) Insert \t(2) Select \t(3) Shell \t\n '))
        init = float(time.time())

        self.merge(colecao, L, ID)

        end = float(time.time())
        print(end - init)
        return colecao

    def select_sort(self, colecao):
        for i in range(len(colecao)):
            # Seleciona índice corrente da série
            minIndex = i
            for j in range(i + 1, len(colecao)):
                if int(colecao[minIndex]['weight']) > int(colecao[j]['weight']):
                    minIndex = j
                    # Se o numero no menor indice for maior que proximo entao troca-se o proximo para o menor indice
            # Ao fim troca se o numero presente no indice da serie pelo menor encontrado
            colecao[i], colecao[minIndex] = colecao[minIndex], colecao[i]
        return colecao

    def shell_sort(self, colecao):
        h = 3
        # Escolha de gap(h)
        n = len(colecao)
        while h > 0:
            # Laço feito ao tamanho do gap
            for i in range(h, n):
                # Percorre o vetor com o gap
                # Salvando temporariamente um "key" que sera comparado para o reordenamento
                temp = colecao[i]
                j = i
                while j >= h and int(temp["weight"]) < int(colecao[j - h]["weight"]):
                    # Compara de modo analogo ao insert
                    colecao[j] = colecao[j - h]
                    j = j - h
                # Se caso o laço não seja satisfeito então o temp -- key -- é colocado na posição de j
                colecao[j] = temp
            h = int(h / 2.2)
        return colecao

    def insert_sort(self, colecao):
        for i in range(1, len(colecao)):
            key = colecao[i]
            j = i - 1
            while j >= 0 and int(key['weight']) < int(colecao[j]['weight']):
                colecao[j + 1] = colecao[j]
                j -= 1
            colecao[j + 1] = key
        return colecao

    def merge(self, colecao, L, ID):

        if len(colecao) > L:
            # Sera dividido até o tamanho L
            meio = int(len(colecao) // 2)
            E = colecao[:meio]
            D = colecao[meio:]
            # Divide-se a estrutura
            self.merge(E, L, ID)
            self.merge(D, L, ID)

            i = j = k = 0

            # Copia dado para colecao de E[] e D[]
            while i < len(E) and j < len(D):
                if int(E[i]['weight']) < int(D[j]['weight']):
                    colecao[k] = E[i]
                    i += 1
                else:
                    colecao[k] = D[j]
                    j += 1
                k += 1

            # Verifica se resta algum elemento a ser ordenado
            while i < len(E):
                colecao[k] = E[i]
                i += 1
                k += 1

            while j < len(D):
                colecao[k] = D[j]
                j += 1
                k += 1
        else:
            if ID == 2:
                self.select_sort(colecao)
            elif ID == 3:
                self.shell_sort(colecao)
            elif ID == 1:
                self.insert_sort(colecao)

        return colecao


class MergeSortFinal(object):
    def ordenar(self, colecao):
        L = int(input('Digite um tamanho L : \n'))
        ID = int(input('\n Digite um ID >>>> (1) Insert \t(2) Select \t(3) Shell \t\n '))
        init = float(time.time())

        self.merge(colecao, L)

        if ID == 2:
            self.select_sort(colecao)
        elif ID == 3:
            self.shell_sort(colecao)
        elif ID == 1:
            self.insert_sort(colecao)
        # Insert definido como padrão

        end = float(time.time())
        print(end - init)

        return colecao

    def select_sort(self, colecao):
        for i in range(len(colecao)):
            # Seleciona índice corrente da série
            minIndex = i
            for j in range(i + 1, len(colecao)):
                if int(colecao[minIndex]['weight']) > int(colecao[j]['weight']):
                    minIndex = j
                    # Se o numero no menor indice for maior que proximo entao troca-se o proximo para o menor indice
            # Ao fim troca se o numero presente no indice da serie pelo menor encontrado
            colecao[i], colecao[minIndex] = colecao[minIndex], colecao[i]
        return colecao

    def shell_sort(self, colecao):
        h = 1
        n = len(colecao)
        while h > 0:
            for i in range(h, n):
                temp = colecao[i]
                j = i
                while j >= h and int(temp["weight"]) < int(colecao[j - h]["weight"]):
                    colecao[j] = colecao[j - h]
                    j = j - h
                    colecao[j] = temp
            h = int(h / 2.2)
        return colecao

    def insert_sort(self, colecao):
        for i in range(1, len(colecao)):
            key = colecao[i]
            j = i - 1
            while j >= 0 and int(key['weight']) < int(colecao[j]['weight']):
                colecao[j + 1] = colecao[j]
                j -= 1
            colecao[j + 1] = key
        return colecao

    def merge(self, colecao, L):
        if len(colecao) > L:
            # Sera dividido até o tamanho L
            meio = int(len(colecao) // 2)
            E = colecao[:meio]
            D = colecao[meio:]
            # Divide-se a estrutura
            self.merge(E, L)
            self.merge(D, L)

            i = j = k = 0

            # Copia dado para colecao de E[] e D[]
            while i < len(E) and j < len(D):
                if int(E[i]['weight']) < int(D[j]['weight']):
                    colecao[k] = E[i]
                    i += 1
                else:
                    colecao[k] = D[j]
                    j += 1
                k += 1

            # Verifica se resta algum elemento a ser ordenado
            while i < len(E):
                colecao[k] = E[i]
                i += 1
                k += 1

            while j < len(D):
                colecao[k] = D[j]
                j += 1
                k += 1
        return colecao


class QuickSortParcial(object):
    def ordenar(self, colecao):
        L = int(input('Digite um tamanho L :'))
        id = int(input('\n Digite um ID  >>>> (1) Insert \t  (2) Select (3) Shell \t\n '))
        init = float(time.time())
        self.quick(colecao, 0, len(colecao) - 1, L, id)
        end = float(time.time())
        print(end - init)
        return colecao

    def select_sort(self, colecao):
        for i in range(len(colecao)):
            # Seleciona índice corrente da série
            minIndex = i
            for j in range(i + 1, len(colecao)):
                if int(colecao[minIndex]['weight']) > int(colecao[j]['weight']):
                    minIndex = j
                    # Se o numero no menor indice for maior que proximo entao troca-se o proximo para o menor indice
            # Ao fim troca se o numero presente no indice da serie pelo menor encontrado
            colecao[i], colecao[minIndex] = colecao[minIndex], colecao[i]
        return colecao

    def shell_sort(self, colecao):
        h = 1
        n = len(colecao)
        while h > 0:
            for i in range(h, n):
                temp = colecao[i]
                j = i
                while j >= h and int(temp["weight"]) < int(colecao[j - h]["weight"]):
                    colecao[j] = colecao[j - h]
                    j = j - h
                    colecao[j] = temp
            h = int(h / 2.2)
        return colecao

    def insert_sort(self, colecao):
        for i in range(1, len(colecao)):
            key = colecao[i]
            j = i - 1
            while j >= 0 and int(key['weight']) < int(colecao[j]['weight']):
                colecao[j + 1] = colecao[j]
                j -= 1
            colecao[j + 1] = key
        return colecao

    def quick(self, colecao, esq, dir, L, id):
        i = esq
        j = dir
        p = colecao[esq + (dir - esq) // 2]
        if L < dir - esq + 1:
            while i <= j:
                while int(colecao[i]['weight']) < int(p['weight']):
                    i += 1
                while int(colecao[j]['weight']) > int(p['weight']):
                    j -= 1

                if i <= j:
                    colecao[i], colecao[j] = colecao[j], colecao[i]
                    i += 1
                    j -= 1
            if L < j:  # se o tamanho ainda não esta em L aplica-se o quick (esquerda)
                self.quick(colecao, esq, j, L, id)

            if L < dir:  # se o tamanho ainda não esta em L aplica-se o quick (direita
                self.quick(colecao, i, dir, L, id)
        else:
            vet = colecao[esq:dir]
            i = 0
            if id == 1:
                self.insert_sort(vet)
            elif id == 2:
                self.select_sort(vet)
            else:
                self.shell_sort(vet)
            for id in range(esq, dir):
                colecao[id] = vet[i]
                i += 1
    #O else serve para fazer a ordenção requerida nos parciais
        return colecao


class QuickSortFinal(object):
    def ordenar(self, colecao):
        L = int(input('Digite um tamanho L : \n'))
        ID = int(input('\n Digite um ID >>>> (1) Insert \t  (2) Select (3) Shell \t\n '))
        init = float(time.time())

        if ID == 2:
            self.select_sort(colecao)
        elif ID == 3:
            self.shell_sort(colecao)
        else:
            self.insert_sort(colecao)
        # Insert definido como padrão

        end = float(time.time())
        print(end - init)

        return colecao

    def quick(self, colecao, esq, dir, L):
        i = esq
        j = dir
        col = colecao[esq + (dir - esq) // 2]
        while i <= j:
            while int(colecao[i]['weight']) < int(col['weight']):
                i += 1
            while int(colecao[j]['weight']) > int(col['weight']):
                j -= 1

            if i <= j:
                colecao[i], colecao[j] = colecao[j], colecao[i]
                i += 1
                j -= 1

        if L < j - esq + 1:  # se o tamanho ainda não esta em L aplica-se o quick (esquerda)
            self.quick(colecao, esq, j, L)

        if L < dir - i + 1:  # se o tamanho ainda não esta em L aplica-se o quick (direita
            self.quick(colecao, i, dir, L)

        return colecao

    def select_sort(self, colecao):
        for i in range(len(colecao)):
            # Seleciona índice corrente da série
            minIndex = i
            for j in range(i + 1, len(colecao)):
                if int(colecao[minIndex]['weight']) > int(colecao[j]['weight']):
                    minIndex = j
                    # Se o numero no menor indice for maior que proximo entao troca-se o proximo para o menor indice
            # Ao fim troca se o numero presente no indice da serie pelo menor encontrado
            colecao[i], colecao[minIndex] = colecao[minIndex], colecao[i]
        return colecao

    def shell_sort(self, colecao):
        h = 1
        n = len(colecao)
        while h > 0:
            for i in range(h, n):
                temp = colecao[i]
                j = i
                while j >= h and int(temp["weight"]) < int(colecao[j - h]["weight"]):
                    colecao[j] = colecao[j - h]
                    j = j - h
                    colecao[j] = temp
            h = int(h / 2.2)
        return colecao

    def insert_sort(self, colecao):
        for i in range(1, len(colecao)):
            key = colecao[i]
            j = i - 1
            while j >= 0 and int(key['weight']) < int(colecao[j]['weight']):
                colecao[j + 1] = colecao[j]
                j -= 1
            colecao[j + 1] = key
        return colecao
