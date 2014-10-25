import datetime

from django.db import models
from django.utils import timezone

class Question(models.Model):
	questionText = models.CharField(max_length = 200)
	pub_date = models.DateTimeField('publishing date')

	def __str__(self):
		return self.questionText

	def was_published_recently(self):
		return self.pub_date >= timezone.now() - datetime.timedelta(days=1)

class Choice(models.Model):
	question = models.ForeignKey(Question)
	choiceText = models.CharField(max_length = 200)
	votes = models.IntegerField(default = 0)

	def __str__(self):
		return self.choice.choiceText
