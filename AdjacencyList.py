
from collections import defaultdict
import csv


graph = defaultdict(list)

allmoviesarray = [ ]
genresmovie = []

def addEdge(graph,u,v):
    graph[u].append(v)

def generate_edges(graph):
    edges = []
  
    # for each node in graph
    for node in graph:
          
        # for each neighbour node of a single node
        for neighbour in graph[node]:
              
            # if edge exists then append
            edges.append((node, neighbour))
    return edges

#def calculate_edges(list1,list2):

  #  is_edge = False

  #  if list1[]:
 #       is_edge = True

  #  return is_edge

def common_data(list1, list2):
    result = False
  
    for x in list1:  
        for y in list2:    
            if x == y:
                result = True
                return result                   
    return result

def initialize_graph():
    
    with open('TestData.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                print(f'Column names are {", ".join(row)}')
                line_count += 1
            else:
                movie = [row[0], row[1], row[2], row[3], row[4]]
                allmoviesarray.append(movie)
                print(f'Title: {allmoviesarray[line_count-1][0]} \tYear: {allmoviesarray[line_count-1][1]} \tGenre:{allmoviesarray[line_count-1][2]} \tCountry: {allmoviesarray[line_count-1][3]} \t Rating: {allmoviesarray[line_count-1][4]}.')
            
                
                if 'Comedy' in allmoviesarray[line_count-1][2]:
                    genresmovie.append(allmoviesarray[line_count-1][0])
                
                #for i in genresmovie:
                 #   if i == 'comedy':
                        
                

                line_count += 1

        print(f'Processed {line_count} lines.')

def printRecommended():
    count = 0
    for i in genresmovie:
        print(i)
        if count == 20:
            break
        count += 1
    

def find_path(graph, start, end, path=[]):
    path = path + [start]
    if start == end:
        return path
    for node in graph[start]:
        if node not in path:
            newpath = find_path(graph, node, end, path)
            if newpath:
                return newpath

# function to generate all possible paths
def find_all_paths(graph, start, end, path =[]):
  path = path + [start]
  if start == end:
    return [path]
  paths = []
  for node in graph[start]:
    if node not in path:
      newpaths = find_all_paths(graph, node, end, path)
    for newpath in newpaths:
      paths.append(newpath)
  return paths


# function to find the shortest path
def find_shortest_path(graph, start, end, path =[]):
        path = path + [start]
        if start == end:
            return path
        shortest = None
        for node in graph[start]:
            if node not in path:
                newpath = find_shortest_path(graph, node, end, path)
                if newpath:
                    if not shortest or len(newpath) < len(shortest):
                        shortest = newpath
        return shortest


def main():

    pref = input('Enter your base movie: ')
    print(pref + " sucks")
    initialize_graph()

    print('Printing Recommended Movies: ')
    printRecommended()
    





main()