import numpy as np
import pandas as pd
from mlxtend.frequent_patterns import apriori, association_rules

csv_path = "A:/Academic/apriori-sr/test_r.csv"
csv_path2 = "A:/Academic/apriori-sr/test_m.csv"



def main():
    def removeAllOcurrencesOfValueInList(_list, value):
        return list(filter(lambda x: x != value, _list))

    confidence_arr = [0.3,0.5,0.7]

    all_ratings = pd.read_csv(csv_path,nrows=110)
    all_movies = pd.read_csv(csv_path2,nrows=11)

    all_movies['genres'] = all_movies.genres.str.split('|')
    #print(all_movies.head())


    all_movies['year'] = all_movies.title.str.extract('(\(\d\d\d\d\))',expand=False)
    all_movies['year'] = all_movies.year.str.extract('(\d\d\d\d)',expand=False)
    all_movies['title'] = all_movies.title.str.replace('(\(\d\d\d\d\))','')
    all_movies['title'] = all_movies['title'].apply(lambda x: x.strip())

    #Classify by Title Demand

    all_movies['title'] = all_movies.title.str.split('|')
    #print(all_movies.head())

    movie_to_id = pd.merge(all_ratings,all_movies,on='movieId')
    movie_to_id.drop('genres',axis=1,inplace=True)
    movie_to_id.drop('year',axis=1,inplace=True)
    movie_to_id.drop('timestamp',axis=1,inplace=True)
    movie_to_id.drop('rating',axis=1,inplace=True)
    aggregation_functions = {'title': 'sum', 'movieId': 'sum'}
    df_new = movie_to_id.groupby(movie_to_id['userId']).aggregate(aggregation_functions)

    #print(df_new.sort_values(by='userId').head())
    #print(movie_to_id.sort_values(by='userId').head())

    copy_movie_to_id = df_new.copy()
    for index, row in df_new.iterrows():
        for title in row['title']:
            copy_movie_to_id.at[index,title] = True
    copy_movie_to_id = copy_movie_to_id.fillna(False)
    #print(copy_movie_to_id.head())

    copy_movie_to_id.drop('title',axis=1,inplace=True)
    copy_movie_to_id.drop('movieId',axis=1,inplace=True)
    #copy_movie_to_id.drop('userId',axis=1,inplace=True)



    '''
    #Classify by Genre
    copy_all_movies = all_movies.copy()
    for index, row in all_movies.iterrows():
        for genre in row['genres']:
            copy_all_movies.at[index,genre] = True
    copy_all_movies = copy_all_movies.fillna(False)
    #print(copy_all_movies.head())


    all_ratings.drop('timestamp',axis=1,inplace=True)
    all_ratings.drop('rating',axis=1,inplace=True)
    #print(all_ratings.head())

    
    movie_to_id = pd.merge(all_ratings,copy_all_movies,on='movieId')

    print(movie_to_id.sort_values(by='userId').head())
    
    copy_movie_to_id = movie_to_id.copy()
    copy_movie_to_id.drop('movieId',axis=1,inplace=True)
    copy_movie_to_id.drop('userId',axis=1,inplace=True)
    copy_movie_to_id.drop('title',axis=1,inplace=True)
    copy_movie_to_id.drop('genres',axis=1,inplace=True)
    copy_movie_to_id.drop('year',axis=1,inplace=True)
    
    #cols = copy_movie_to_id.columns.tolist()
    '''
    #print(cols)
    #print(copy_movie_to_id.head())
    
    frequent_itemsets = apriori(copy_movie_to_id, min_support = 0.01, use_colnames = True)
    print("Maiores Suportes :")
    print(frequent_itemsets.sort_values(by=['support'], ascending = False).head(5))
    print("Menores Suportes :")
    print(frequent_itemsets.sort_values(by=['support'], ascending = True).head(5))



    rules = association_rules(frequent_itemsets, metric="confidence",min_threshold=confidence_arr[0])
    print("Maior Força - ","Confiança Mínima de ",confidence_arr[0] )
    print(rules.sort_values(by=['confidence'], ascending = False).drop(['lift','support','antecedent support', 'consequent support', 'leverage', 'conviction'], axis=1).head(5))
    print("Menor Força - ","Confiança Mínima de ",confidence_arr[0] )
    print(rules.sort_values(by=['confidence'], ascending = True).drop(['lift','support','antecedent support', 'consequent support', 'leverage', 'conviction'], axis=1).head(5))

    rules = association_rules(frequent_itemsets, metric="confidence",min_threshold=confidence_arr[1])
    print("Maior Força - ","Confiança Mínima de ",confidence_arr[1] )
    print(rules.sort_values(by=['confidence'], ascending = False).drop(['lift','support','antecedent support', 'consequent support', 'leverage', 'conviction'], axis=1).head(5))
    print("Menor Força - ","Confiança Mínima de ",confidence_arr[1] )
    print(rules.sort_values(by=['confidence'], ascending = True).drop(['lift','support','antecedent support', 'consequent support', 'leverage', 'conviction'], axis=1).head(5))

    rules = association_rules(frequent_itemsets, metric="confidence",min_threshold=confidence_arr[2])
    print("Maiores Suportes - ","Confiança Mínima de ",confidence_arr[2] )
    print(rules.sort_values(by=['confidence'], ascending = False).drop(['lift','support','antecedent support', 'consequent support', 'leverage', 'conviction'], axis=1).head(5))
    print("Menor Força - ","Confiança Mínima de ",confidence_arr[2] )
    print(rules.sort_values(by=['confidence'], ascending = True).drop(['lift','support','antecedent support', 'consequent support', 'leverage', 'conviction'], axis=1).head(5))
    print("Maiores Suportes - Por Lift ","Confiança Mínima de ",confidence_arr[2] )
    print(rules.sort_values(by=['lift'], ascending = False).drop(['antecedent support', 'consequent support', 'leverage', 'conviction'], axis=1).head(3))
    rules = association_rules(frequent_itemsets, metric="confidence",min_threshold=0.5)
    print('Regras mais fortes para',"Confiança Determinada de ","0.5" )
    print(rules.sort_values(by=['confidence','lift'], ascending = [False,False]).drop(['support','antecedent support', 'consequent support', 'leverage', 'conviction'], axis=1).tail())
    
    pass

if __name__ == '__main__':
    main()