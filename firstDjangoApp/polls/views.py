from django.shortcuts import render
from django.http import HttpResponse
def index(abc):
    return HttpResponse("this is my first view!")

def detail(request, qID):
	return HttpResponse("This is the %s question." % qID)

def results(request, qID):
	response = "This is the results of question %s."
	return HttpResponse(response % qID)

def vote(request, qID):
	return HttpResponse("You want to vote %s question." % qID)
