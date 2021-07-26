# COP-3530-Project-3-pleY-Reviews

Worst Zip Codes by Yelp Reviews
pleY Reviews
By Nicholas Bonhoure, Peter Hoang, Anthony Liao

Problem:
We are trying to find the worst zip code in a city in terms of yelp reviews so that
someone using our program can know which areas to avoid when visiting. Most
review websites and programs only sort by highest or best ratings, however we
want to use the premise of worst rated to sort and search businesses.

Motivation:
Yelp lets users search for best business in terms of ratings, reviews, or their
“recommended”, but no search capabilities for worst businesses. We want to
know what areas to avoid, but have no way of doing so through the yelp
interface.

Features:
● Inputs a city and returns a list of all the the zip codes from worst to best,
ranking based on most low star businesses (less than 2-3 stars) (this will
be the function that we will be timing between two different implementation
of structures)

● Input city and star rating to return a list of businesses that are of the star
rating and in the city

● Input a zip code and returns a list of the worst businesses, worst at the top
and descending

● Input “worst business” and returns the worst business in the United States


Data:
The data set we will be using is the Yelp Open Dataset which provides statistics
for various business attributes such as location, star rating, and number of
reviews.
Link: https://www.yelp.com/dataset

Tools:
We will be using C++ as our programming language and we will use Visual
Studio as our IDE. We will be using the terminal for input and output.

Visuals:
We will be using a text based menu selection from within the IDE, in the terminal

Strategy:
We will be implementing a Min Heap and a Map for our main algorithm we are looking to
time: searching by city, inserting zip codes into the structure- ordered by most
terrible businesses, and returning the list. We plan on searching the dataset,
finding which zip codes have the most low rated businesses, and inserting into
each structure, then printing it. Other functions may not be timed but exist for
functionality.

Distribution of Responsibility and Roles:
● Search dataset, menu, worst in usa - Anthony

● Map , worst business by zip - Peter

● Min heap , worst business by zip, video - Nicholas

● Project submission - Nicholas


References:
● “Yelp Open Dataset.” Yelp Dataset, Yelp, www.yelp.com/dataset.
The Yelp dataset from which we will be drawing our data
from.
● “Visual Studio IDE, Code Editor, Azure DevOps, & App Center.” Visual
Studio, Microsoft, 28 June 2021, visualstudio.microsoft.com/.
The primary IDE we will be using for development.
