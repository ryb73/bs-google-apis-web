open Js.Promise;

let client = Google.Client.init "client_id" [| `YouTubeSSL, `YouTubeReadOnly |];

let doSearch () => {
    let opts = { "part": "snippet", "q": "query", "maxResults": Js.undefined };
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
};

let doListPlaylists () => {
    let opts = Google.YouTube.Playlists.listOptions part::"id" mine::Js.true_ ();
    Google.YouTube.Playlists.list opts
        |> then_ (fun data => {
            data##result##items
                |> Js.Array.forEach (fun item => {
                    Js.log @@ "id: " ^ item##id;
                });

            resolve ();
        })
        |> catch (fun err => {
            Js.log err;
            resolve ();
        });
};

let doInsertPlaylist () => {
    let opts = Google.YouTube.Playlists.insertOptions part::"id" title::"new list" ();
    Google.YouTube.Playlists.insert opts
        |> then_ (fun data => {
            Js.log data##result##id;
            resolve ();
        })
        |> catch (fun err => {
            Js.log err;
            resolve ();
        });
};

let doYouTubeStuff () => {
    doSearch ();
    doListPlaylists ();
    doInsertPlaylist ();
    ();
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
