from django.conf.urls import patterns, url
from polls import views
urlpatterns = patterns(
    '',
    url(r'^$', views.index, name='index'),
	url(r'^(?P<qID>\d+)/$', views.detail, name='detail'),
	url(r'^(?P<qID>\d+)/results/$', views.results, name='results'),
	url(r'^(?P<qID>\d+)/vote/$', views.vote, name='vote'),
)
