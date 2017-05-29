type item;

type insertResult = {.
    result: Js.t item
};

type insertOptions = Js.t {.
    part: string,
    snippet: Js.t {.
        playlistId: string,
        resourceId: Js.t {.
            kind: Js.undefined string,
            videoId: string
        }
    }
};

let insertOptions ::playlistId ::videoId () => {
    "part": "id",
    "snippet": {
        "playlistId" : playlistId,
        "resourceId": {
            "kind": Js.undefined,
            "videoId": videoId
        }
    }
};

external _insert : insertOptions => Js.t insertResult = "gapi.client.youtube.playlists.insert" [@@bs.val];
let insert opts => GooglePromise.convert @@ _insert opts;