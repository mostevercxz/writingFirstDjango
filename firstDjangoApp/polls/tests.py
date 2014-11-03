from django.test import TestCase

import datetime
from django.test import TestCase
from django.utils import timezone
from polls.models import Question
from django.core.urlresolvers import reverse

class QuestionMethodTests(TestCase):
	def test_was_published_recently_with_future_pub_date(self):
		time = timezone.now() + datetime.timedelta(days=30)
		future_question = Question(pub_date = time)
		self.assertEqual(future_question.was_published_recently(), False)

def createQ(qText, days):
	time = timezone.now() + datetime.timedelta(days = days)
	return Question.objects.create(questionText = qText, pub_date = time)


class QuestionViewTests(TestCase):
	def test_index_view_with_no_question(self):
		response = self.client.get(reverse('polls:index'))
		self.assertEqual(response.status_code, 200)
		self.assertContains(response, 'No polls are available.')
		self.assertQuerysetEqual(response.context['latestQuestion'], [])

	def test_index_view_with_a_past_question(self):
		createQ(qText='Past Question', days=-10)
		response = self.client.get(reverse('polls:index'))
		self.assertQuerysetEqual(response.context['latestQuestion'],['<Question: Past question>'])
