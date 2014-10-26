from django.shortcuts import render
from django.http import HttpResponse
def index(abc):
    return HttpResponse("this is my first view!")
