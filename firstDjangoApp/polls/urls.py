from django.conf.urls import patterns, url
from polls import views
''' method 1
urlpatterns = patterns(
    '',
    url(r'^$', views.index, name='index'),
	url(r'^(?P<qID>\d+)/$', views.detail, name='detail'),
	url(r'^(?P<qID>\d+)/results/$', views.results, name='results'),
	url(r'^(?P<qID>\d+)/vote/$', views.vote, name='vote'),
)'''

urlpatterns = patterns(
	'',
	url(r'^$', views.IndexView.as_view(), name='index'),
	url(r'^(?P<pk>\d+)/$', views.DetailView.as_view(), name='detail'),
	url(r'^(?P<qID>\d+)/results/$', views.results, name='results'),
	url(r'^(?P<qID>\d+)/vote/$', views.vote, name='vote'),
)
