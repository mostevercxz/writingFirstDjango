from django.contrib import admin
from polls.models import Question

class QA(admin.ModelAdmin):
	fields = ['pub_date', 'questionText']


admin.site.register(Question, QA)
