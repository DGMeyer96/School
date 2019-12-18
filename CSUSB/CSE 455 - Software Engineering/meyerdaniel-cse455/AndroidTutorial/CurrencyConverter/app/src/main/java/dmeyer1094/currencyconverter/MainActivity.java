package dmeyer1094.currencyconverter;

import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class MainActivity extends AppCompatActivity
{
    private EditText editText;
    private Button btn;
    private TextView textView;
    private String usd;

    //Exchange rate URL
    private static final String url = "https://api.fixer.io/latest?base=USD";

    //Stores buffered JSON string from website
    String json = "";

    String line = "";

    //Holds value needed for conversion
    String rate = "";

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //Set variable to their respective UI elements
        editText = (EditText)findViewById(R.id.EditText);
        btn = (Button)findViewById(R.id.btn);
        textView = (TextView)findViewById(R.id.Yen);

        //Event for btn being clicked
        btn.setOnClickListener(new View.OnClickListener()
        {
            //Required function for listener
            @Override
            public void onClick(View convertToYen)
            {
                System.out.println("\nTESTING 1 ... Before AsynchExecution\n");

                new BackgroundTask.execute();

                System.out.println("\nTESTING 2 ... After AsynchExecution\n");
            }
        });
    }

    private class BackgroundTask extends AsyncTask<Void, Void, String>
    {
        @Override
        protected void onPreExecute()
        {
            super.onPreExecute();
        }

        @Override
        protected void onProgressUpdate(Void... values)
        {
            super.onProgressUpdate(values);
        }

        @Override
        protected void onPostExecute(String result)
        {
            super.onPostExecute(result);
        }

        @Override
        protected String doInBackground(Void... params) {
            try {
                URL web_url = new URL(MainActivity.this.url);

                HttpURLConnection httpURLConnection = (HttpURLConnection) web_url.openConnection();

                httpURLConnection.setRequestMethod("GET");

                System.out.println("\nTESTING ... BEFORE connection method to URL\n");

                httpURLConnection.connect();

                InputStream inputStream = httpURLConnection.getInputStream();

                BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));

                System.out.println("CONNECTION SUCCESSFUL\n");

                line = bufferedReader.readLine();
                while (line != null) {
                    json += line;
                    line = bufferedReader.readLine();
                }
                System.out.println("\nTHE JSON: " + json);

                JSONObject obj = new JSONObject("json_string");

                JSONObject objRate = obj.getJSONObject("rates");

                rate = objRate.get("JPY").toString();
                System.out.println("\nWhat is rate: " + rate + "\n");

                System.out.println("\nTesting JSON String Exchange Rate INSIDE AsynchTask:" +
                        " (append this string with your variable of type double," +
                        " obtained from the String variable, rate");


                //covert user's input to string
                usd = editText.getText().toString();
                //if-else statement to make sure user cannot leave the EditText blank
                if (usd.equals(""))
                {
                    textView.setText("This field cannot be blank!");
                }
                else
                {
                    //Convert string to double
                    Double input = Double.parseDouble(usd);
                    //USD to YEN conversion
                    Double convert = Double.parseDouble(rate);
                    Double result = input * convert;
                    //Display converted value
                    textView.setText("$" + usd + " = " + "¥" + String.format("%.2f", result));
                    // clear after clicking
                    editText.setText("");
                }
            }
            catch (MalformedURLException e)
            {
                e.printStackTrace();
            }
            catch (IOException e)
            {
                e.printStackTrace();
            }
            catch (JSONException e)
            {
                Log.e("MYAPP", "unexpected JSON exception", e);
                System.exit(1);
            }
            return null;
        }
    }
}


