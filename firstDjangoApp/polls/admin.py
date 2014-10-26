from django.contrib import admin
from polls.models import Question,Choice

var = 1

# class ChoiceInline(admin.StackedInline):
class ChoiceInline(admin.TabularInline):
	model = Choice
	extra = 5

class QA(admin.ModelAdmin):
	fieldsets = [
		#('111', {'fields':['pub_date'], 'classes':['collapse']}),
		('main info', {'fields':['questionText', 'pub_date']}),
	]
	list_display = ('questionText','pub_date', 'was_published_recently')
	list_filter = ['pub_date']
	search_fields = ['questionText']
	inlines = [ChoiceInline]


import pdb
pdb.set_trace()
admin.site.site_header = "go fuck ahead!!"
var = var + 1
admin.site.register(Question, QA)
