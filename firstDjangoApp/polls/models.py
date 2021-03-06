import datetime

from django.db import models
from django.utils import timezone

class Question(models.Model):
	questionText = models.CharField(max_length = 200)
	pub_date = models.DateTimeField('publishing date')

	def __str__(self):
		return self.questionText

	def was_published_recently(self):
		now = timezone.now()
		return now >= self.pub_date >= now - datetime.timedelta(days=1)
	was_published_recently.admin_order_field = 'pub_date'
	was_published_recently.short_description = 'en??'
	was_published_recently.boolean = True

class Choice(models.Model):
	question = models.ForeignKey(Question)
	choiceText = models.CharField(max_length = 200)
	votes = models.IntegerField(default = 0)

	def __str__(self):
		return self.choiceText
