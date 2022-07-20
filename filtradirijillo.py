#Se cargan librerías a utilizar

import pandas as pd
import time
import os
from pathlib import Path


#Se lee el dataset original, debe estar en la misma ubicación que el script
data= pd.read_csv("dataset-proyecto.csv")


#Se obtiene el directorio actual, es importante para filtrar mediante las stopwords
x=os.getcwd()



#Los filtros se almacenan en una carpeta llamada Filtros, en la misma ubicación que el script

fuente=x+"/Filtros"  #Aquí se debe modificar el string "fuente" dependiendo de como se escriban los directorios 


os.chdir(fuente) #Se cambia a la carpeta de stopwords

#Se crea una lista con las stopwords seleccionadas
stopwords=[]
lista=os.listdir(fuente)
for i in lista:
    if i[-4:]==".txt":
        tracks=open(i)
        tracks=tracks.readlines()
        for k in tracks:
            flag=0
            if len(k)>1:
                if k[-1]=="\n":
                    word=k[:-1]
                    stopwords.append(word)
                    flag=1
            if flag==0:
                stopwords.append(k)


os.chdir(x) #Se vuelve a la carpeta del script


#Esta función filtra los textos a partir de los símbolos del alfabeto, para ello utilizamos su codificación en unicode
#y mantenemos aquellas palabras que no contienen símbolos de codificación mayor a 879. También, se convierten todas las letras
# a minúsculas, y eliminamos las palabras que corresponden a enlaces web y las stopwords

def filtroalfab(dataset):
    start=time.time()
    filtroidioma=[]
    for i in range(len(dataset)):
        texto=data['TweetText'][i].lower().split()
        newtext=[]
        for j in texto:
            flag=0
            if j in stopwords:
                flag=1
            if len(j)>4:
                if j[0:4]=="http":
                    flag=1
            for k in j:
                if ord(k)>879:
                       flag=1
            if flag==0:
                newtext.append(j)
        nue=" ".join(newtext)
        filtroidioma.append(nue)
    end=time.time()
    print(end-start)
    return filtroidioma

# Filtramos los textos eliminando los símbolos que se detallan a continuación

def filtrosymb(datos):
    simb="! # · $ % & / ( ) = ? ¡ ' ¿ | ~ ½ ¬ { [ ] } | ¬ ° ´ ´ + } { - . , ; : _ [ ] *  ~ ^ ` ̣· , \" ".split()
    start=time.time()
    filtrosimb=[]
    for i in range(len(datos)):
        texto=datos[i]
        newtext=[]
        for j in texto:
            if j not in simb:
                newtext.append(j)
        nue="".join(newtext)
        nue=nue.split()
        nue=" ".join(nue)
        filtrosimb.append(nue)
    end=time.time()
    print(end-start)
    return filtrosimb

#Creamos un nuevo dataset cambiando los textos de los tweets por los textos filtrados
twitid=[]
usid=[]
date=[]
for i in range(len(data)):
    twitid.append(data["TweetId"][i])
    usid.append(data["UserId"][i])
    date.append(data["TweetDate"][i])

datosf=filtroalfab(data)
datossi=filtrosymb(datosf)

DatasetF=pd.DataFrame({"TweetId":twitid,"TweetDate":date,"TweetText":datossi,"UserId":usid})

#Se convierte a un nuevo csv en el directorio actual
DatasetF.to_csv("Dataset_Filtrado.csv",index=False)

