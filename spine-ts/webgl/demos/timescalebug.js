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
            animationState = skeletonObjects.state,
            trackEntry,
            t;


        animationState.setAnimation(0, 'scale_2_200_ms', false);
        trackEntry = animationState.addAnimation(0, 'translate_100_ms', false, -0.05);

        trackEntry.mixDuration = 0.05;

        for (t = 0; t < 153; t++) {
            update(skeleton, animationState, 0.001);
        }

        trackEntry.timeScale = 0;

        for (t = 0; t < 1; t++) {
            update(skeleton, animationState, 0.001);
        }

        trackEntry.timeScale = 1;

        for (t = 0; t < 150; t++) {
            update(skeleton, animationState, 0.001);
        }

        console.log('Scale should be as setup pose (1), but is ' + skeleton.findBone('bone').scaleX);
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
