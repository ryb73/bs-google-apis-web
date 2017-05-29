type snippet = {.
    channelId: string,
    title: string,
    description: string,
    channelTitle: string,
    defaultLanguage: string
};

type item = {.
    id: string,
    snippet: Js.t snippet
};

type listResult = {.
    result: Js.t {. items: array (Js.t item) }
};

type listOptions;
external listOptions :
    part::string =>
    channelId::string? =>
    id::string? =>
    mine::Js.boolean? => unit => listOptions = "" [@@bs.obj];

external _list : listOptions => Js.t listResult = "gapi.client.youtube.playlists.list" [@@bs.val];
let list opts => GooglePromise.convert @@ _list opts;

type insertResult = {.
    result: Js.t item
};

type insertOptions = Js.t {.
    part: string,
    snippet: Js.t {.
        title: string,
        description: Js.undefined string
    },
    status: Js.undefined (Js.t {.
        privacyStatus: Js.undefined string
    })
};

let insertOptions ::part ::title ::description=? ::privacyStatus=? () => {
    let status = switch privacyStatus {
        | None => Js.undefined
        | Some x => Js.Undefined.return {
            "privacyStatus": Js.Undefined.return x
        }
    };

    {
        "part": part,
        "snippet": {
            "title" : title,
            "description": Js.Undefined.from_opt description
        },
        "status": status
    };
};

external _insert : insertOptions => Js.t insertResult = "gapi.client.youtube.playlists.insert" [@@bs.val];
let insert opts => GooglePromise.convert @@ _insert opts;