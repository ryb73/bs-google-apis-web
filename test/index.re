open Js.Promise;

let client = Google.Client.init "client_id" [| `YouTubeSSL, `YouTubeReadOnly |];

client
    |> then_ (fun _ => {
        let auth = Google.Auth2.getAuthInstance ();

        if(auth##isSignedIn##get ()) {
            ();
        } else {
            auth##signIn ();
        };

        auth##isSignedIn##listen (fun _ => ());

        resolve ();
    });