import datetime

from algoritmosDeOrdenacao import *
from grafo import Grafo
from utils import *

'''
Implemente o algoritmo de ordenação no arquivo algoritmosDeOrdenacao.py
Instruções básicas de como fazer a implementação estão no arquivo algoritmosDeOrdenacao.py
'''

if __name__ == "__main__":

    ''' trecho original para definições
    algoritimoDeOrdenacao = InsertionSort()
    arquivoJson = '../grafos/7vertices.json'
    '''
    # trecho alterado para as definições

    '''Apresentção e escolha do numero de vertices - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Um arquivo de grafos foi definido como padrão para prevenir erros
    variaveis 'strini' e 'strfin' são usadas para gerar um nome para o arquivo de saida com base no arquivo de entrada
    elas serão concatenadas
    '''

    strini = ''  # Arquivo usado
    stropc = ''  # Opçao usada
    strfin = '_Vertices_Output.txt'
    print("Escolha a quantidade de vertices:\n")
    ver = input("1 - 7 vertices\n2 - 100 vertices\n3 - 1000 vertices\n4 - 10000 vertices\n5 - 100000 vertices\n")

    if int(ver) == 1:
        arquivoJson = '../grafos/7vertices.json'
        strini = '7'

    elif int(ver) == 2:
        arquivoJson = '../grafos/100vertices.json'
        strini = '100'

    elif int(ver) == 3:
        arquivoJson = '../grafos/1000vertices.json'
        strini = '1000'

    elif int(ver) == 4:
        arquivoJson = '../grafos/10000vertices.json'
        strini = '10000'

    elif int(ver) == 5:
        arquivoJson = '../grafos/100000vertices.json'
        strini = '100000'

    else:
        # entrada padrão
        print("Nenhum tamanho de entrada apresentado foi selecionado")
        print("Neste caso o padrão será 100\n")
        arquivoJson = '../grafos/100vertices.json'
        strini = '100'

    '''
    Apresentação e escolha do algoritimo de ordenação - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Um algoritimo foi definido como padrão para não ocasionar erros
    '''

    print("Escolha o algoritmo de ordenação:\n")
    index = input("1 - QuickSort\n2 - MergeSort\n3 - InsertionSort\n4 - MergeSortParcial\n"
                "5 - MergeSortFinal \n6 - QuickSortParcial\n7 - QuickSortFinal\n")
    if int(index) == 1:
        algoritimoDeOrdenacao = QuickSort()
        stropc = 'Quick'
    elif int(index) == 2:
        algoritimoDeOrdenacao = MergeSort()
        stropc = 'Merge'
    elif int(index) == 3:
        algoritimoDeOrdenacao = InsertSort()
        stropc = 'Insert'
    elif int(index) == 4:
        algoritimoDeOrdenacao = MergeSortParcial()
        stropc = 'MergeParcial'
    elif int(index) == 5:
        algoritimoDeOrdenacao = MergeSortFinal()
        stropc = 'MergeFinal'
    elif int(index) == 6:
        algoritimoDeOrdenacao = QuickSortParcial()
        stropc = 'QuickParcial'
    elif int(index) == 7:
        algoritimoDeOrdenacao = QuickSortFinal()
        stropc = 'QuickFinal'

    else:
        # algoritimo padrão
        print("Nenhum algoritmo apresentado foi selecionado")
        print("Neste caso será usado o InsertionSort definido como padrão\n")
        algoritimoDeOrdenacao = InsertSort()

    arquivoDeSaida = '../arvores_geradas/' + strini + stropc + strfin   # concatenação das strings para gerar um nome para o arquivo de saida

    #print("algoritmo iniciou em: ", datetime.datetime.now())

    grafo = Grafo()
    grafo.estabelecerAlgoritmoDeOrdencao(algoritimoDeOrdenacao)
    grafo.carregarGrafo(arquivoJson)

    arvoreGeradoraMinima = grafo.executarKruskal()
    print("Gerando arquivo, aguarde ...")
    SalvarArvoreGeradoraMinimaEmArquivo(arquivoDeSaida, arvoreGeradoraMinima)

    #print("algoritmo terminou em: ", datetime.datetime.now())
