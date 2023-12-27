#include<iostream>
#include<string>
#include<cpprest/http_client.h>
#include<cpprest/filestream.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {

	cout << "WEATHER APP" << endl;
	cout << "\tEnter City name: ";
	string city;
	getline(cin, city);

	http_client client(U("https://api.openweathermap.org/data/2.5"));

	uri_builder builder(U("/weather"));
	builder.append_query(U("q"), utility::conversions::to_string_t(city));
	builder.append_query(U("AppID"), U("0014dd057823505b6881559371ea370f"));

	http_request request(methods::GET);
	request.set_request_uri(builder.to_string());

	client.request(request).then([](http_response response)  {
		return response.extract_json();
	}
	).then([](web::json::value body) {
		cout << "\tTemperature: "<< body[U("main")][U("temp")].as_double()<<"K"<<endl;
		cout << "\tHumidity: " << body[U("main")][U("humidity")].as_double() << "%" << endl;
		cout << "\tWeather: " << utility::conversions::to_utf8string(body[U("weather")][0][U("main")].as_string());
		}
	).wait();

	return 0;

}