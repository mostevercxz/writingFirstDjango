from django.shortcuts import render,get_object_or_404
from django.http import HttpResponse, Http404,HttpResponseRedirect
from polls.models import Question,Choice
from django.template import RequestContext, loader
from django.views import generic

# part 4,add generic view
class IndexView(generic.ListView):
	template_name = 'polls/index.html'
	context_object_name = 'latestQuestion'

	def get_queryset(self):
		return Question.objects.order_by('-pub_date')[:5]

class DetailView(generic.DetailView):
	model = Question
	template_name = 'polls/detail.html'

class ResultsView(generic.DetailView):
	model = Question
	template_name = 'polls/results.html'

def index(abc):
	latestQuestion = Question.objects.order_by('-pub_date')[:5]
	#output = ','.join([p.questionText for p in latestQuestion])
	#return HttpResponse(output)
	#
	# method 2:
	#template = loader.get_template('polls/index.html')
	#context = RequestContext(abc, {
	#	'latestQuestion' : latestQuestion,
	#})
	#return HttpResponse(template.render(context))
	#
	# method 3:
	context = {'latestQuestion', latestQuestion}
	return render(abc, 'polls/index.html', context)

def detail(request, qID):
	#method 1:
	#try:
	#	question = Question.objects.get(pk=qID)
	#except Question.DoesNotExist:
	#	raise Http404
	question = get_object_or_404(Question, pk = qID)
	return render(request, 'polls/detail.html', {'question':question})
	#return HttpResponse("This is the %s question." % qID)

def results(request, qID):
	question = get_object_or_404(Question, pk=qID)
	return render(request, 'polls/results.html', {'question':question})
	# method 1
	#response = "This is the results of question %s."
	#return HttpResponse(response % qID)


from django.core.urlresolvers import reverse
def vote(request, qID):
	p = get_object_or_404(Question, pk = qID)
	try:
		selected_choice = p.choice_set.get(pk = request.POST['choice'])
	except (KeyError, Choice.DoesNotExist):
		return render(request, 'polls/detail.html', {
			'question':p,
			'error_message':"YOu need to select a choice!!",
		})
	else:
		selected_choice.votes += 1
		selected_choice.save()
	return HttpResponseRedirect(reverse('polls:results', args=(p.id,)))
	#return HttpResponse("You want to vote %s question." % qID)
