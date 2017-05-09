open Js.Promise;

let client = Google.Client.init "client_id" [| `YouTubeSSL, `YouTubeReadOnly |];

let doYouTubeStuff a => {
    let opts = [%bs.obj { part: "snippet", q: "query", maxResults: Js.undefined }];
    Google.YouTube.Search.list opts
        |> then_ (fun data => {
            data##result##items
                |> Js.Array.forEach (fun item => {
                    Js.log item##id##videoId;
                });

            resolve ();
        })
        |> catch (fun err => {
            Js.log err;
            resolve ();
        });

    Js.log a;
};

client
    |> then_ (fun _ => {
        let auth = Google.Auth2.getAuthInstance ();

        if(auth##isSignedIn##get ()) {
            ();
        } else {
            auth##signIn ();
        };

        auth##isSignedIn##listen (fun _ => doYouTubeStuff ());

        resolve ();
    });