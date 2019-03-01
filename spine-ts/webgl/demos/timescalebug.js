var timeScaleBugDemo = function(canvas, bgColor) {
    var assetManager;

    var DEMO_NAME = "TimeScale Bug Demo";

    function init () {
        assetManager = spineDemos.assetManager;
        assetManager.loadJson(DEMO_NAME, "TimeScaleBug.json");
    }

    function loadingComplete () {
        startTest(loadSkeleton("Skeleton"));
    }

    function startTest (skeletonObjects) {
        var skeleton = skeletonObjects.skeleton,
            animationState = skeletonObjects.state;


        var track0From = animationState.setAnimation(0, 'translate_100_ms', false);
        var track0To = animationState.addAnimation(0, 'translate_100_ms', false, 0);


        update(skeleton, animationState, 0.12);
        // First a tick big enough so the next animation should be started.

        track0From.timeScale = 0;
        track0To.timeScale = 0;

        update(skeleton, animationState, 0.1);
        //This update causes division by 0 followed by multiplication by 0 - result is NaN

        console.log('trackTime on track0To is NaN: ' + isNaN(track0To.trackTime));
    }

    function update (skeleton, animationState, dt) {
        animationState.update(dt);
        animationState.apply(skeleton);
        skeleton.updateWorldTransform();
    }

    function loadSkeleton(name, animation, sequenceSlots) {
        var attachmentLoader = {
            'newRegionAttachment': function() {},
            'newBoundingBoxAttachment': function() {},
            'newMeshAttachment': function() {},
            'newPathAttachment': function() {},
            'newPointAttachment': function() {},
            'newClippingAttachment': function() {}
        };

        var skeletonJson = new spine.SkeletonJson(attachmentLoader);
        var skeletonData = assetManager.get(DEMO_NAME, "TimeScaleBug.json");
        var spineSkeletonData = skeletonJson.readSkeletonData(skeletonData);
        var skeleton = new spine.Skeleton(spineSkeletonData);
        var state = new spine.AnimationState(new spine.AnimationStateData(spineSkeletonData));

        return {
            skeleton: skeleton,
            state: state,
        };
    }

    function render () {
    }

    timeScaleBugDemo.loadingComplete = loadingComplete;
    timeScaleBugDemo.render = render;
    timeScaleBugDemo.DEMO_NAME = DEMO_NAME;
    init();
};
